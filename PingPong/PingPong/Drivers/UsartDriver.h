/*
 * UsartDriver.h
 *
 * Created: 28.08.2015 15:43:45
 *  Author: ketilgs
 */ 


#ifndef USARTDRIVER_H_
#define USARTDRIVER_H_

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );

#endif /* USARTDRIVER_H_ */