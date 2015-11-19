/*
 * CFile1.c
 *
 * Created: 02.10.2015 13:37:52
 *  Author: sverrevr
 */ 
#include "mcp2515.h"
#include "spi.h"
#include "MCP2515_register.h"


uint8_t mcp2515_read(uint8_t addr){
	clear_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Activates CAN controller
	SPI_communicate(MCP_READ);		//Sends instruction
	SPI_communicate(addr);			//Sends the address
	uint8_t val = SPI_communicate(0x00);	//Receives data
	set_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Deactivates.
	return val;
}

void mcp2515_write(uint8_t addr, uint8_t data){
	clear_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Activates CAN controller
	SPI_communicate(MCP_WRITE);		//Sends instruction
	SPI_communicate(addr);			//Sends the address
	SPI_communicate(data);			//Sends data
	set_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Deactivates.
}

uint8_t mcp2515_read_status(){
	clear_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Activates CAN controller
	SPI_communicate(MCP_READ_STATUS);	//Sends instruction
	uint8_t val = SPI_communicate(0x00);
	set_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Deactivates
	return val;
}


void mcp2515_request_to_send(uint8_t reg){
	clear_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Activates CAN controller
	SPI_communicate(reg);			//Sends instruction
	set_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Deactivates
}

void mcp2515_bit_modify(uint8_t addr, uint8_t mask, uint8_t data){
	clear_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Activates CAN controller
	SPI_communicate(MCP_BITMOD);		//Sends instruction
	SPI_communicate(addr);
	SPI_communicate(mask);
	SPI_communicate(data);
	set_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Deactivates
}

void mcp2515_reset(){
	clear_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Activates CAN controller
	SPI_communicate(MCP_RESET);		//Sends instruction
	set_bit(SLAVE_CS_REG, SLAVE_CS_BIT);	//Deactivates
}
