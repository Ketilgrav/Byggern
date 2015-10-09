/*
 * UsartDriver.c
 *
 * Created: 28.08.2015 15:43:58
 *  Author: ketilgs
 */ 
#include "../MainInclude/MainInclude.h"
#include "UsartDriver.h"

void USART_init(){
	//ubbr = F_CPU
	int baudRate = BAUD;  //Burde vi bruke BAUD fra h fila her? og burde BAUD være 19200?
	unsigned int ubrr = F_CPU/(16*baudRate) -1;
	//Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	//Enable receiver and transmitter
	UCSR0B	 = (1<<RXEN0)|(1<<TXEN0);
		//RXEN:  Aktiverer USART receiver
		//TXEN: Aktiverer USART transmitter
		
	
	//Set frame format: 8data, 2stop bit
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
		//URSEL: Skriver til UCSRC istedet for UBRRH, ved 1.
		//USBS0: Antall stop bits, 0->1bit, 1->2bit
		//UCZ0/1/2: Character size 011->8bit. 
		
	//Slik at vi kan bruke printf;
	fdevopen(USART_Transmit,USART_Receive);
}

void USART_Transmit( unsigned char data ){

	//Wait for empty transmit buffer
	while( !( UCSR0A & (1<<UDRE0)) );

	//Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char USART_Receive(void){
	
	//Wait for data to be received
	while( !(UCSR0A & (1<<RXC0)) );
	//Get and return received data from buffer
	return UDR0;
}
