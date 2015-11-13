/*
 * Game.c
 *
 * Created: 25.09.2015 16:51:47
 *  Author: sverrevr
 */ 

#include "Game.h"
uint8_t runGame(Controls* controls, CAN_message* msgOut){
	oled_mem_clear();
	oled_mem_print("SPILLET KJORER", 3, 0);
	char a[5];
	sprintf(a, "%i", controls->js.x_percent);
	char b[5];
	sprintf(b, "%i", controls->js.y_percent);
	oled_mem_print(a, 4, 0);
	oled_mem_print(b, 5, 0);
	
	if(msgOut->length == 0){
		msgOut->data[CANMSG_PUSH_BYTE] = 0;
	}
	
		 //if ((controls->btns.A_count) % 2){
	msgOut->data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_MOTORSIGNALS;
	if(controls->btns.A){
		msgOut->data[CANMSG_PUSH_BYTE] = 0xFF;	
	}
	msgOut->data[CANMSG_SERVO] = controls->sliders.r_percent;
	msgOut->data[CANMSG_MOTOR] = controls->js.x_percent;
	char c[5];
	//printf(c, "%u", controls->btns.A_count);
	oled_mem_print(c, 6, 0);
		//}
		/*else{
			msgOut->data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_MOTORSIGNALS;
			msgOut->data[CANMSG_SERVO] = controls->js.x_percent;
			msgOut->data[CANMSG_MOTOR] = controls->sliders.r_percent;
			char c[5];
			sprintf(c, "%u", controls->btns.A_count);
			oled_mem_print(c, 6, 0);
		}*/
	msgOut->length = CANMSG_LEN;
	msgOut->id = 0b00100000001;
	msgOut->priority = 2;
	return 0;
}
