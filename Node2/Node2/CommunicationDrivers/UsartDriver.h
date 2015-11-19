/*
 * UsartDriver.h
 *
 * Created: 28.08.2015 15:43:45
 *  Author: ketilgs
 */ 


#ifndef USARTDRIVER_H_
#define USARTDRIVER_H_

#include "../MainInclude.h"

#define BAUD 19200UL
#define UBRR (F_CPU/(16UL*BAUD) - 1)

void USART_init();
void USART_transmit( unsigned char data );
unsigned char USART_receive(void);

#endif /* USARTDRIVER_H_ */
