/*
 * PingPong.c
 *
 * Created: 28.08.2015 11:32:04
 *  Author: ketilgs
 */ 

//Bytt til den fancy screen moden, gir bonus.

#include "MainInclude/MainInclude.h"
#include "Drivers/UsartDriver.h"
#include "Drivers/external_SRAM.h"
#include "Drivers/ADC_Driver.h"
#include "Drivers/Controllers.h"
#include "Drivers/OLED.h"
#include "UI/Menu.h"

int main(void){
	USART_INIT();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	SRAM_INIT();
	ADC_init();
	OLED_init();
	set_bit(DDRB, PB0);
	
	controllers_init();
	JoyStick js;
	Slider s_l;
	Slider s_r;
	joystick_calibrate(&js);
	s_l.channel = 3;
	s_r.channel = 2;
	
	printf("\n\n\n");
	
	menyNode* menu = menu_init();
	
	
	unsigned short mainLoopCounter = 0;	
    while(1){
		mainLoopCounter++;
		if(!(mainLoopCounter%10)){
			toggle_bit(PORTB, PB0);
		}
		joystick_update(& js);
		menu_go(&menu, &js);		
    }
}