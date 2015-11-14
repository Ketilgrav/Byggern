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
#include "../MainInclude.h"

typedef struct CAN_message{
	uint16_t id;
	uint8_t length;
	int8_t data[8];
	uint8_t priority; //0b00 - 0b11
} CAN_message;

typedef enum {NOINT = 0b000, ERR = 0b001, RX0 = 0b110, RX1 = 0b111 } interrupt;

#define interrupt_DDR DDRD
#define interrupt_PIN PIND
#define interrupt_bit PD3

void CAN_init();
//void CAN_error();
void CAN_transmit_complete();
uint8_t CAN_data_receive(CAN_message* msg, uint8_t reg);
uint8_t CAN_message_send(CAN_message const * const msg);
void CAN_message_send_to_reg(CAN_message const * const msg, uint8_t reg);
interrupt CAN_int();

void CAN_int_clear(interrupt CAN_interrupt);
uint8_t interruptToMask(interrupt CAN_interrrupt);
void CAN_all_int_clear();



#endif /* CAN_H_ */