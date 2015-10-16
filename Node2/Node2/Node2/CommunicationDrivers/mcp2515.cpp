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
	clear_bit(slave_cs_reg, slave_cs_bit);	//Aktiverer can controller
	SPI_communicate(MCP_READ);				//Sender instruksjon
	SPI_communicate(addr);					//Sender adressen
	uint8_t val = SPI_communicate(0x00);	//Tar imot data
	set_bit(slave_cs_reg, slave_cs_bit);	//deaktiverer.
	return val;
}

void mcp2515_write(uint8_t addr, uint8_t data){
	clear_bit(slave_cs_reg, slave_cs_bit);	//Aktiverer can controller
	SPI_communicate(MCP_WRITE);				//Sender instruksjon
	SPI_communicate(addr);					//Sender adressen
	SPI_communicate(data);					//Sender data
	set_bit(slave_cs_reg, slave_cs_bit);	//deaktiverer.
}

uint8_t mcp2515_read_status(){
	clear_bit(slave_cs_reg, slave_cs_bit);	//Aktiverer can controller
	SPI_communicate(MCP_READ_STATUS);		//Sender instruksjon
	uint8_t val = SPI_communicate(0x00);
	set_bit(slave_cs_reg, slave_cs_bit);	//deaktiverer.
	return val;
}


void mcp2515_request_to_send(uint8_t reg){
	clear_bit(slave_cs_reg, slave_cs_bit);	//Aktiverer can controller
	SPI_communicate(reg);					//Sender instruksjon
	set_bit(slave_cs_reg, slave_cs_bit);	//deaktiverer.
}

void mcp2515_bit_modify(uint8_t addr, uint8_t mask, uint8_t data){
	clear_bit(slave_cs_reg, slave_cs_bit);	//Aktiverer can controller
	SPI_communicate(MCP_BITMOD);			//Sender instruksjon
	SPI_communicate(addr);
	SPI_communicate(mask);
	SPI_communicate(data);
	set_bit(slave_cs_reg, slave_cs_bit);	//deaktiverer.
}

void mcp2515_reset(){
	clear_bit(slave_cs_reg, slave_cs_bit);	//Aktiverer can controller
	SPI_communicate(MCP_RESET);				//Sender instruksjon
	set_bit(slave_cs_reg, slave_cs_bit);	//deaktiverer.
}