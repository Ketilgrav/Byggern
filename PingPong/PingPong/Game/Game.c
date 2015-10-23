/*
 * Game.c
 *
 * Created: 25.09.2015 16:51:47
 *  Author: sverrevr
 */ 
#include "../MainInclude/MainInclude.h"
#include "../Drivers/Controllers.h"
#include "../Communication_drivers/can.h"

uint8_t runGame(JoyStick* js, JoyStick* js_old, Slider* s_l, Slider* s_r){
	oled_mem_clear();
	oled_mem_print("SPILLET KJORER",3,0);
	char a[5];
	sprintf(a,"%i",js->x_percent);
	char b[5];
	sprintf(b,"%i",js->y_percent);
	oled_mem_print(a,4,0);
	oled_mem_print(b,5,0);
	
	//if(js_old->x_percent == js->x_percent && js_old->y_percent == js->y_percent){
		//return 0;
	//}
	
	CAN_message msgOut0;
	msgOut0.data[0] = s_r->percent;
	msgOut0.data[1] = s_r->voltage;
	msgOut0.length = 2;
	msgOut0.id = 0b00100000001;
	msgOut0.priority = 2;
	
	CAN_message_send(&msgOut0);
	//_delay_ms(20);
	*js_old = *js;
	return 0;
}
