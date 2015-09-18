/*
 * PingPong.c
 *
 * Created: 28.08.2015 11:32:04
 *  Author: ketilgs
 */ 


#include "MainInclude/MainInclude.h"
#include "Drivers/UsartDriver.h"
#include "Drivers/external_SRAM.h"
#include "Drivers/ADC_Driver.h"
#include "HW_Controll/Controllers.h"
#include "HW_Controll/OLED.h"
#include "Etc/Font.h"

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
	
	unsigned short mainLoopCounter = 0;
    while(1){
		mainLoopCounter++;
		if(!(mainLoopCounter%10)){
			toggle_bit(PORTB, PB0);
		}
		joystick_update(&js);
		slider_update(&s_l);
		slider_update(&s_r);
		printf("X: %i    \t", js.x_percent);
		printf("Y: %i    \t", js.y_percent);
		printf("L: %i    \t", s_l.percent);
		printf("R: %i    \t", s_r.percent);
		printf("BR: %i    \t", read_bit(PINB,PB2));
		printf("BL: %i    \t", read_bit(PINB,PB3));
		printf("BJS: %i    \t\r", read_bit(PINB,PB4));
		
		for(int i= 0; i<8;++i){
			oled_data = font[44][i];
		}
		for(int i= 0; i<8;++i){
			oled_data = font[47][i];
		}
		for(int i= 0; i<8;++i){
			oled_data = font[44][i];
		}
		oled_controll = 0xB0 | (mainLoopCounter%8);//setter pagen
		oled_controll = 0x00;	//LSB til startpunkt
		oled_controll = 0x10;	//MSB
		//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		
    }
}