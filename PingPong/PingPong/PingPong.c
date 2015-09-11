/*
 * PingPong.c
 *
 * Created: 28.08.2015 11:32:04
 *  Author: ketilgs
 */ 


#include "MainInclude/MainInclude.h"
#include "Drivers/UsartDriver.h"
#include "Drivers/external_SRAM.h"

int main(void){
	USART_Init();
	SRAM_INIT();
	set_bit(DDRB, PB0);
	
	unsigned short mainLoopCounter = 0;
    while(1){
		if(!(mainLoopCounter%10)){
			toggle_bit(PORTB, PB0);
		}
		mainLoopCounter++;
		exit(0);
    }
}