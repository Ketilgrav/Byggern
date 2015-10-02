/*
 * mcp2515.h
 *
 * Created: 02.10.2015 13:38:50
 *  Author: sverrevr
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_

#define can_cs_bit
#define can_cs_reg 

#define usart_transmit_adress 0b00110000
#define usart_

uint8_t mcp2515_read(uint8_t addr);	
void mcp2515_write(uint8_t addr, uint8_t data);	
void mcp2515_request_to_send(uint8_t reg); //send dataen din over can
void mcp2515_bit_modify(uint8_t addr, uint8_t mask, uint8_t data); //skriver en del av register
void mcp2515_reset();
void mcp2515_read_status();





#endif /* MCP2515_H_ */