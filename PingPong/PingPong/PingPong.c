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
#include "HW_Controll/JoyStick.h"

int main(void){
	USART_Init();
	SRAM_INIT();
	ADC_init();
	set_bit(DDRB, PB0);
	
	
	JoyStick js;
	joystick_calibrate(&js);
	
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	unsigned short mainLoopCounter = 0;
    while(1){
		mainLoopCounter++;
		if(!(mainLoopCounter%10)){
			toggle_bit(PORTB, PB0);
		}
		joystick_update(&js);
		printf("X: %i      \t", js.x_voltage);
		printf("Y: %i      \t", js.y_voltage);
		printf("fdfdf: %u           \r", (js.x_voltage - js.x_rest));
		
    }
}