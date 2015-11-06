/*
 * Game.c
 *
 * Created: 25.09.2015 16:51:47
 *  Author: sverrevr
 */ 
#include "../MainInclude/MainInclude.h"
#include "../Drivers/Controllers.h"
#include "../Communication_drivers/can.h"
#include "../../../InterNodeHeaders/CanMessageFormat.h"

uint8_t runGame(Controls* controls){
	oled_mem_clear();
	oled_mem_print("SPILLET KJORER", 3, 0);
	char a[5];
	sprintf(a, "%i", controls->js.x_percent);
	char b[5];
	sprintf(b, "%i", controls->js.y_percent);
	oled_mem_print(a, 4, 0);
	oled_mem_print(b, 5, 0);
	
	
	
 	CAN_message msgOut0;
 	if ((controls->btns.A_count) % 2){
		msgOut0.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_MOTORSIGNALS;
		msgOut0.data[CANMSG_SERVO] = controls->sliders.r_percent;
		msgOut0.data[CANMSG_MOTOR] = controls->js.x_percent;
		char c[5];
		sprintf(c, "%u", controls->btns.A_count);
		oled_mem_print(c, 6, 0);
	}
	else{
		msgOut0.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_MOTORSIGNALS;
		msgOut0.data[CANMSG_SERVO] = controls->js.x_percent;
		msgOut0.data[CANMSG_MOTOR] = controls->sliders.r_percent;
		char c[5];
		sprintf(c, "%u", controls->btns.A_count);
		oled_mem_print(c, 6, 0);
	}
	msgOut0.length = CANMSG_LEN;
	msgOut0.id = 0b00100000001;
	msgOut0.priority = 2;
	
	CAN_message_send(&msgOut0);
	return 0;
}
