/*
 * spi.c
 *
 * Created: 02.10.2015 13:38:20
 *  Author: sverrevr
 */ 

#include "spi.h"

void SPI_init(void){
	/* Set MOSI and SCK output, all others input */
	set_bit(master_out_ddr, master_out_bit);
	clear_bit(master_inn_ddr, master_inn_bit);
	set_bit(slave_clk_ddr, slave_clk_bit);
	set_bit(slave_cs_ddr, slave_cs_bit);
	
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//SPIE, interrupt enable
}

char SPI_communicate(char cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}