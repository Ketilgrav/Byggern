/*
 * UsartDriver.h
 *
 * Created: 28.08.2015 15:43:45
 *  Author: ketilgs
 */ 


#ifndef USARTDRIVER_H_
#define USARTDRIVER_H_

#include "../MainInclude.h"

#define FOSC F_CPU// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_init();
void USART_Transmit( unsigned char data );
unsigned char USART_Receive(void);

#endif /* USARTDRIVER_H_ */