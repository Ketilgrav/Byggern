/*
 * UsartDriver.c
 *
 * Created: 28.08.2015 15:43:58
 *  Author: ketilgs
 */ 
#include "UsartDriver.h"

void USART_init(){

 	//Set baud rate
	UBRR0H = (unsigned char)(UBRR>>8);
	UBRR0L = (unsigned char)UBRR;
	 	
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		//RXEN: Activates USART receiver
		//TXEN: Activates USART transmitter
		
	
	//Set frame format: 8data, 2stop bit
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
		//URSEL: Writes to UCSRC instead of UBRRH, when 1.
		//USBS0: Number of stop bits, 0->1bit, 1->2bit
		//UCZ0/1/2: Character size 011->8bit. 
	//Enable printf;
	fdevopen(&USART_transmit, &USART_receive);
}

void USART_transmit(unsigned char data){
	//Wait for empty transmit buffer
	while( !(UCSR0A&(1<<UDRE0)) );

	//Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char USART_receive(void){
	//Wait for data to be received
	while( !(UCSR0A&(1<<RXC0)) );
	//Get and return received data from buffer
	return UDR0;
}
