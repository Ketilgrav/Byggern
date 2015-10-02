/*
 * can.h
 *
 * Created: 02.10.2015 13:38:33
 *  Author: sverrevr
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "mcp2515.h"
#include "MCP2515_register.h"

typedef struct can_message{
	unsigned short id;
	uint8_t length;
	uint8_t data[8];
} can_message;

void CAN_init();
CAN_message_send();
CAN_error();
CAN_transmit_complete();
CAN_data_receive();
CAN_int_vect();



#endif /* CAN_H_ */