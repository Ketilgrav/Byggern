/*
 * can.c
 *
 * Created: 02.10.2015 13:37:21
 *  Author: sverrevr
 */ 


void CAN_init(){
	uint8_t value;
	SPI_init(); // Initialize SPI
	mcp2515_reset(); // Send reset-command
	
	// Self-test
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in configuration mode after reset!\n");
	}
		
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);	
}

//Standard send inn MCP_TXB0CTRL
void CAN_message_send(can_message* msg, uint8_t reg){
	//mcp2515_write(usart_transmit_adress|MCP_TXB0CTRL, balka);
	mcp2515_write(usart_transmit_adress|(reg + 1), msg->id>>3); //Setter de 8 msb av id
	mcp2515_write(usart_transmit_adress|(reg + 2), msg->id<<5);	//De 3 lsb av id
	mcp2515_write(usart_transmit_adress|(reg + 5), msg->length);	//Data length. Kan sette RTR ved å | med 0b01000000
	
	for(uint8_t i = 0; i<msg.length; ++i){
		mcp2515_write(usart_transmit_adress|(MCP_TXB0CTRL + i+6), msg->data[i]);
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

void CAN_data_receive(can_message* msg){
	
}