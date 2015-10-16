
#include "CommunicationDrivers/can.h"
#include "MainInclude/MainInclude.h"

void setup(){
	CAN_init();
	interrupt CAN_interrupt;
	
	CAN_message msgInn0;
	CAN_message msgInn1;
}

void loop(){
	CAN_interrupt = CAN_int();
	
	switch(CAN_interrupt){
		case NOINT:
		break;
		case ERR:
		break;
		case RX0:
		CAN_data_receive(&msgInn0, MCP_RXB0CTRL);
		msgInn0.data[0] = '-';
		msgInn0.data[1] = 's';
		msgInn0.id = 0b11000000001;
		CAN_message_send(msgInn0);
		break;
		case RX1:
		CAN_data_receive(&msgInn1, MCP_RXB1CTRL);
		msgInn1.data[0] = '-';
		msgInn1.data[1] = '<';
		msgInn1.id = 0b01000000001;
		CAN_message_send(msgInn1);
		break;
		default:
		break;
	}
	CAN_int_clear(CAN_interrupt);
}
