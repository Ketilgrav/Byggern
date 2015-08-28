/*
 * PingPong.c
 *
 * Created: 28.08.2015 11:32:04
 *  Author: ketilgs
 */ 


#include "MainInclude/MainInclude.h"

int main(void)
{
	set_bit(DDRB,PB0);
    while(1)
    {
		set_bit(PORTB,PB0);
		_delay_ms(300);
		clear_bit(PORTB,PB0);
		_delay_ms(700);
        //TODO:: Please write your application code 
    }
}