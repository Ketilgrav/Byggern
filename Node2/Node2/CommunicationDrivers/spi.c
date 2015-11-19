/*
 * spi.c
 *
 * Created: 02.10.2015 13:38:20
 *  Author: sverrevr
 */ 

#include "spi.h"

void SPI_init(void){
	/* Set MOSI and SCK output, all others input */
	set_bit(MASTER_OUT_DDR, MASTER_OUT_BIT);
	clear_bit(MASTER_INN_DDR, MASTER_INN_BIT);
	set_bit(SLAVE_CLK_DDR, SLAVE_CLK_BIT);
	set_bit(SLAVE_CS_DDR, SLAVE_CS_BIT);
	
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//SPIE, interrupt enable
}

char SPI_communicate(char cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while( !(SPSR&(1<<SPIF)) );
	return SPDR;
}
