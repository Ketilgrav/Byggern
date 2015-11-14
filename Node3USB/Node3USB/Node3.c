/*
 * Node3.c
 *
 * Created: 10.11.2015 09:35:38
 *  Author: sverrevr
 */ 

#include "MainInclude.h"
#include "Communication_drivers/USB.h"
#include "TouchDrivers/oled.h"

int main(){
	USB_init();
	_delay_ms(300);
	
	oled_init();
	oled_home();
	//oled_print("Touch test!");
	while(1){
		if(UHINT & DCONNI){
			oled_print("1");
			oled_home();
		}
		else{
			oled_print("0");
			oled_home();
		}
		
	}
	return 0;
}