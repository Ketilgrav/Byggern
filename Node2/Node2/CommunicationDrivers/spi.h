/*
 * spi.h
 *
 * Created: 02.10.2015 13:38:27
 *  Author: sverrevr
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../MainInclude.h"

#define SLAVE_CS_BIT 0
#define SLAVE_CS_REG PORTB
#define SLAVE_CS_DDR DDRB

#define SLAVE_CLK_BIT 1
#define SLAVE_CLK_REG PORTB
#define SLAVE_CLK_DDR DDRB

#define MASTER_OUT_BIT 2
#define MASTER_OUT_REG PORTB
#define MASTER_OUT_DDR DDRB

#define MASTER_INN_BIT 3
#define MASTER_INN_REG PORTB
#define MASTER_INN_PIN PINB
#define MASTER_INN_DDR DDRB

//#define SPI_DELAY_TIME_uS

char SPI_communicate(char cData);
void SPI_init();



#endif /* SPI_H_ */
