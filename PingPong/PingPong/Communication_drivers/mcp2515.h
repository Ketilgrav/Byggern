/*
 * mcp2515.h
 *
 * Created: 02.10.2015 13:38:50
 *  Author: sverrevr
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_

#include "../MainInclude.h"
#include "spi.h"


uint8_t mcp2515_read(uint8_t addr);
void mcp2515_write(uint8_t addr, uint8_t data);	
void mcp2515_request_to_send(uint8_t reg); 
void mcp2515_bit_modify(uint8_t addr, uint8_t mask, uint8_t data);
void mcp2515_reset();
uint8_t mcp2515_read_status();


#endif /* MCP2515_H_ */
