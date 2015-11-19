/*
 * can.c
 *
 * Created: 02.10.2015 13:37:21
 *  Author: sverrevr
 */ 

#include "can.h"

#include <stdio.h>
#include <string.h>

void CAN_init(){
	clear_bit(INTERRUPT_DDR, INTERRUPT_BIT); //Input on the interrupt pin
	
	uint8_t value;
	SPI_init(); // Initialize SPI
	mcp2515_reset(); // Send reset-command
	_delay_us(20);
	// Self-test
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		puts("MCP2515 is NOT in configuration mode after reset!\n");
	}
		
	//Sets up RXBOCTRL
		//RXM = 01, activate filter, only short ID
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_RXB0RXM_MASK, 1 << 5);
		//BUKT: 1 -> transfers to RXB1 when RXB0 is full
	mcp2515_bit_modify(MCP_RXB0CTRL, MCP_RXB0BUKT_MASK, 1 << 2);
	//RXB1CTRL
		//RXM = 01, activate filter, only short ID
	mcp2515_bit_modify(MCP_RXB1CTRL, MCP_RXB1RXM_MASK, 1 << 5);
	
	//Set interrupt enable
	//MERRE = 0 Message error interrupt
	//WAKIE = 0 (We dont use sleep)
	//ERRIE = 1 Error interrupt 
	//TX2IE = 0 Transmit 2 empty interrupt
	//TX1IE = 0 Transmit 1 empty interrupt
	//TX0IE = 0 Transmit 0 empty interrupt
	//RX1IE = 1 Interrupt when there is data RX1
	//RX0IE = 1 Interrupt when there is data RX2
	mcp2515_write(MCP_CANINTE, 0b00100011);
	
	//Filters:
	//Mask for RX0
	mcp2515_write(MCP_RXM0SIDH, NODE1_CANID_H_MASK >> 3);
	mcp2515_bit_modify(MCP_RXM0SIDL, 0b11100000U, NODE1_CANID_H_MASK << 5);
	
	//Mask for RX1
	mcp2515_write(MCP_RXM1SIDH, NODE1_CANID_L_MASK >> 3);
	mcp2515_bit_modify(MCP_RXM1SIDL, 0b11100000U, NODE1_CANID_L_MASK << 5);
	
	//Filter 0 (RX0, goes to RX1 if RX0 is full)
	mcp2515_write(MCP_RXF0SIDH, NODE1_CANID_HIGHPRIO_0 >> 3);
	mcp2515_bit_modify(MCP_RXF0SIDL, 0b11100000U, NODE1_CANID_HIGHPRIO_0 << 5);
	
	//Filter 1 (RX0, goes to RX1 if RX0 is full)
	mcp2515_write(MCP_RXF1SIDH, NODE1_CANID_HIGHPRIO_1 >> 3);
	mcp2515_bit_modify(MCP_RXF1SIDL, 0b11100000U, NODE1_CANID_HIGHPRIO_1 << 5);
	
	//Filter 2 (RX1)
	mcp2515_write(MCP_RXF2SIDH, NODE1_CANID_0 >> 3);
	mcp2515_bit_modify(MCP_RXF2SIDL, 0b11100000U, NODE1_CANID_0 << 5);
	
	//Filter 3 (RX1)
	mcp2515_write(MCP_RXF3SIDH, NODE1_CANID_1 >> 3);
	mcp2515_bit_modify(MCP_RXF3SIDL, 0b11100000U, NODE1_CANID_1 << 5);
	
	//Filter 4 (RX1)
	mcp2515_write(MCP_RXF4SIDH, NODE1_CANID_2 >> 3);
	mcp2515_bit_modify(MCP_RXF4SIDL, 0b11100000U, NODE1_CANID_2 << 5);
	
	//Filter 5 (RX1)
	mcp2515_write(MCP_RXF5SIDH, NODE1_CANID_3 >> 3);
	mcp2515_bit_modify(MCP_RXF5SIDL, 0b11100000U, NODE1_CANID_3 << 5);
	
	CAN_all_int_clear();
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
}


//Returns 1 if message was sedt, otherwise 0
uint8_t CAN_message_send(CAN_message const * const msg){
	//Finds an available register
	
	//reg0, 0x30: status bit nr 2 
	//reg1, 0x40: status bit nr 4 
	//reg2, 0x50: status bit nr 6
	
	uint8_t status = mcp2515_read_status();
	if(status | (1 << 2)){
		CAN_message_send_to_reg(msg, MCP_TXB0CTRL);
	}
	else if(status | (1<<4)){
		CAN_message_send_to_reg(msg, MCP_TXB1CTRL);
	}
	else if(status | (1<<6)){
		CAN_message_send_to_reg(msg, MCP_TXB2CTRL);
	}
	else{
		return 0;
	}
	return 1;
}

void CAN_message_send_to_reg(CAN_message const * const msg, uint8_t reg){
	//mcp2515_bit_modify(reg, TXP_MASK, msg->priority); 	//Set priority
	mcp2515_write(reg + 1, msg->id>>3); 			//Set 8 MSB of ID
	mcp2515_write(reg + 2, msg->id<<5);			//Set 3 LSB of ID
	mcp2515_write(reg + 5, msg->length);			//Data length. Can set RTR by | with 0b01000000
	
	for(uint8_t i = 0; i<msg->length; ++i){
		mcp2515_write(reg + i+6, msg->data[i]);
	}
	if(reg == MCP_TXB0CTRL){
		mcp2515_request_to_send(MCP_RTS_TX0);
	}
	else if(reg == MCP_TXB1CTRL){
		mcp2515_request_to_send(MCP_RTS_TX1);
	}
	else if(reg == MCP_TXB2CTRL){
		mcp2515_request_to_send(MCP_RTS_TX2);
	}
}

bool CAN_data_receive(CAN_message* msg, uint8_t reg){
	//memset(msg, 0, sizeof(CAN_message));
	
	uint8_t retVal = false;
	//reg0, 0x60: bit nr 0
	//reg1, 0x70: bit nr 1
	uint8_t status = mcp2515_read_status();
	if(status | (1 << ((reg>>4)-6))){
		msg->id = (mcp2515_read(reg+1) << 3); //8 msb
		msg->id |= (mcp2515_read(reg+2) >> 5); //3 lsb
		msg->length = mcp2515_read(reg+5) & 0x0f;
		
		for(uint8_t i=0; i<msg->length && i<8; ++i){
			msg->data[i] = mcp2515_read(reg+6+i);
		}
		retVal = true;
	}	
	return retVal;
}

interrupt CAN_int(){
	if(!read_bit(INTERRUPT_PIN, INTERRUPT_BIT)){
		interrupt retval = (interrupt)((mcp2515_read(MCP_CANSTAT)&MCP_CANSTAT_ICOD_MASK) >> 1);
		return retval;
	}
	return noInt;
}

void CAN_int_clear(interrupt CAN_interrupt){
	if(CAN_interrupt != noInt){
		mcp2515_bit_modify(MCP_CANINTF, interrupt_to_mask(CAN_interrupt), 0x00);	
	}
}

void CAN_all_int_clear(){
	mcp2515_write(MCP_CANINTF, 0x00);
}

uint8_t interrupt_to_mask(interrupt CAN_interrupt){
	switch(CAN_interrupt){
		case noInt:
			return 0x00;
		case err:
			return 0b00100000;
		case rx0:
			return 0b00000001;
		case rx1:
			return 0b00000010;
		default:
			return 0x00;
	}
}
