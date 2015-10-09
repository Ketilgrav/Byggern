/*
 * can.c
 *
 * Created: 02.10.2015 13:37:21
 *  Author: sverrevr
 */ 
#include "can.h"

void CAN_init(){
	clear_bit(interrupt_DDR|interrupt_bit); //Input på interrupt pinen
	
	uint8_t value;
	SPI_init(); // Initialize SPI
	mcp2515_reset(); // Send reset-command
	
	// Self-test
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in configuration mode after reset!\n");
	}
		
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);	
	
	//Setter opp RXBOCTRL
		//RXM = 01, bare valide meldigner med kort id. 
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_RXB0RXM_MASK, 0b01 << 5);
		//BUKT: 1 -> ting går til RXB1 når denne er full
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_RXB0BUKT_MASK, 0b1 << 2);
	//RXB1CTRL
		//RXM = 01
	mcp2515_bit_modify(MCP_RXB1CTRL, MCP_RXB1RXM_MASK, 0b01 << 5);
	
	//Setter interrupt enable
	//MERRE = 0 Message error interrupt
	//WAKIE = 0 (har ikke sleep)
	//ERRIE = 1 Error interrupt (kommer av flere)
	//TX2IE = 0 Transmit 2 empty interrupt
	//TX1IE = 0 Transmit 1 empty interrupt
	//TX0IE = 0 Transmit 0 empty interrupt
	//RX1IE = 1 Interrupt når data på RX1
	//RX0IE = 1 -||- RX2
	mcp2515_write(MCP_CANINTE, 0b10100011);
}


/*Returnerer 1 om meldignen ble sendt, ellers 0*/
uint8_t CAN_message_send(can_message* msg){
	//Finner hvilket register som er ledig
	
	//reg0, 0x30: status bit nr 2 
	//reg1, 0x40: status bit nr 4 
	//reg2, 0x50: status bit nr 6 
	
	uint8_t status = mcp2515_read_status();
	if(status | (1 << 2){
		CAN_message_send_to_reg(msg, MCP_TXB0CTRL);
	}
	else if(status 1 (1<<4)){
		CAN_message_send_to_reg(msg, MCP_TXB1CTRL);
	}
	else if(status 1 (1<<6)){
		CAN_message_send_to_reg(msg, MCP_TXB2CTRL);
	}
	else{
		return 0;
	}
	return 1;
}

void CAN_message_send_to_reg(can_message* msg, uint8_t reg){
	mcp2515_bit_modify(reg, TXP_MASK, msg->priority); //Setter prio
	mcp2515_write(reg + 1, msg->id>>3); //Setter de 8 msb av id
	mcp2515_write(reg + 2, msg->id<<5);	//De 3 lsb av id
	mcp2515_write(reg + 5, msg->length);	//Data length. Kan sette RTR ved å | med 0b01000000
	
	for(uint8_t i = 0; i<msg->length; ++i){
		mcp2515_write(reg + i+6, msg->data[i]);
	}
	if(reg = MCP_TXB0CTRL){
		mcp2515_request_to_send(MCP_RTS_TX0);
	}
	else if(reg = MCP_TXB1CTRL){
		mcp2515_request_to_send(MCP_RTS_TX1);
	}
	else if(reg = MCP_TXB2CTRL){
		mcp2515_request_to_send(MCP_RTS_TX2);
	}	
}

bool CAN_data_receive(can_message* msg, interrupt intr){
	if(intr = RX0){
		return CAN_data_receive(MCP_RXB0CTRL);
	}
	else if( intr = RX1){
		return CAN_data_receive(MCP_RXB1CTRL);
	}
	return false;
}

bool CAN_data_receive(can_message* msg, uint8_t reg){
	uint8_t retVal = false;
	//reg0, 0x60: bit nr 0
	//reg1, 0x70: bit nr 1
	uint8_t status = mcp2515_read_status();
	if(status | (1 << (reg>>4)-6)){
		msg->id = (mcp2515_read(reg+1) << 3); //8 msb
		msg->id |= (mcp2515_read(reg+2) >> 5); //3 lsb
		msg->length = mcp2515_read(reg+5);
		
		for(uint8_t i=0; i<msg->length; ++i){
			msg->data[i] = mcp2515_read(reg+6+i);
		}
		retVal = true;
	}
	
	//Forteller at dataen er lest
	mcp2515_bit_modify(MCP_CANINTF, 1 << (reg>>4)-6), 0);
	return retVal;
}

interrupt CAN_int_vect(){
	if(read_bit(interrupt_PIN,interrupt_bit)){
		return (enum interrupt)((mcp2515_read(MCP_CANSTAT)&MCP_CANSTAT_ICOD_MASK) >> 1);
	}
	return NOINT;
}