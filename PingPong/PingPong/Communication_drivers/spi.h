/*
 * spi.h
 *
 * Created: 02.10.2015 13:38:27
 *  Author: sverrevr
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../MainInclude/MainInclude.h"

#define slave_cs_bit 4
#define slave_cs_reg PORTB
#define slave_cs_ddr DDRB

#define slave_clk_bit 7
#define slave_clk_reg PORTB
#define slave_clk_ddr DDRB

#define master_out_bit 5
#define master_out_reg PORTB
#define master_out_ddr DDRB

#define master_inn_bit 6
#define master_inn_reg PORTB
#define master_inn_pin PINB
#define master_inn_ddr DDRB

#define spi_delay_time_us

char SPI_communicate(char cData);
void SPI_init();



#endif /* SPI_H_ */