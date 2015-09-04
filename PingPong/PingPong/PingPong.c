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
	
	unsigned short mainLoopCounter;
    while(1){
		if(!mainLoopCounter){
			toggle_bit(PORTB, PB0);
		}
		//putchar(getchar());
		SRAM_test();
		mainLoopCounter++;
    }
}