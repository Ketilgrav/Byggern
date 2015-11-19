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
} CAN_message;

typedef enum {noInt = 0b000, err = 0b001, rx0 = 0b110, rx1 = 0b111 } interrupt;

#define INTERRUPT_DDR DDRD
#define INTERRUPT_PIN PIND
#define INTERRUPT_BIT PD3

void CAN_init();
//void CAN_error();
void CAN_transmit_complete();
uint8_t CAN_data_receive(CAN_message* msg, uint8_t reg);
uint8_t CAN_message_send(CAN_message const * const msg);
void CAN_message_send_to_reg(CAN_message const * const msg, uint8_t reg);
interrupt CAN_int();

void CAN_int_clear(interrupt CAN_interrupt);
uint8_t interrupt_to_mask(interrupt CAN_interrupt);
void CAN_all_int_clear();



#endif /* CAN_H_ */
