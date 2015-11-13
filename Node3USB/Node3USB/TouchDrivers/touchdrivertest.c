/*
 * touchdrivertest.c
 *
 * Created: 05.11.2014 18:24:52
 *  Author: Volstad
 */

#include <avr/io.h>
#include "touch.h"
#include "oled.h"
#include <util/delay.h>
#include <stdlib.h>

int mainTest(void)
{
	_delay_ms(300);
	
	oled_init();
	oled_home();
	oled_print("Touch test!");
	
	touch_init(30, 30, 30, 30);
	
	char buffer[10];
	unsigned char left_slider; unsigned char right_slider; unsigned char left_button; unsigned char right_button;
    while(1)
    {
		touch_measure(&left_slider, &right_slider, &left_button, &right_button);
		
		oled_line(1);
		oled_clear_line();
		oled_print(itoa(left_slider, buffer, 10));
		oled_line(2);
		oled_clear_line();
		oled_print(itoa(right_slider, buffer, 10));
		oled_line(3);
		oled_clear_line();
		oled_print(itoa(left_button, buffer, 10));
		oled_print("      ");
		oled_print(itoa(right_button, buffer, 10));
		_delay_ms(25);
    }
}