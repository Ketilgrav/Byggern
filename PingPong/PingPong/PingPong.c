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
		/*joystick_update(&js);
		slider_update(&s_l);
		slider_update(&s_r);
		printf("X: %i    \t", js.x_percent);
		printf("Y: %i    \t", js.y_percent);
		printf("L: %i    \t", s_l.percent);
		printf("R: %i    \t", s_r.percent);
		printf("BR: %i    \t", read_bit(PINB,PB2));
		printf("BL: %i    \t", read_bit(PINB,PB3));
		printf("BJS: %i    \t\r", read_bit(PINB,PB4));*/
		
		
		oled_goto_line(2);
		oled_print("Oystein er ");
		_delay_ms(1000);
		oled_clear_line(2);
		oled_goto_line(4);
		oled_print("ultradust");
		_delay_ms(1000);
		oled_clear_line(4);
		//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		
    }
}