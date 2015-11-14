/*
 * UsartDriver.h
 *
 * Created: 28.08.2015 15:43:45
 *  Author: ketilgs
 */ 


#ifndef USARTDRIVER_H_
#define USARTDRIVER_H_

#include "../MainInclude.h"

#define FOSC 1843200// Clock Speed
#define BAUD 19200
#define MYUBRR FOSC/16/BAUD-1

void USART_init();
void USART_Transmit( unsigned char data );
unsigned char USART_Receive(void);

#endif /* USARTDRIVER_H_ */