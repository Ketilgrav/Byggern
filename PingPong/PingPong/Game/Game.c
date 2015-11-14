/*
 * Game.c
 *
 * Created: 25.09.2015 16:51:47
 *  Author: sverrevr
 */ 

#include "Game.h"
uint8_t runGame(GameState* gameState, Controls* controls, CAN_message* msgOut){
	oled_clear();
	oled_print("SPILLET KJORER", 3, 0);
	char a[5];
	sprintf(a, "%i", controls->jsX.percent);
	char b[5];
	sprintf(b, "%i", controls->jsY.percent);
	oled_print(a, 4, 0);
	oled_print(b, 5, 0);
	
	if(msgOut->length == 0){
		msgOut->data[CANMSG_PUSH_BYTE] = 0;
	}
	
	msgOut->data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_MOTORSIGNALS;
	if(controls->btnR.edge){
		msgOut->data[CANMSG_PUSH_BYTE] = 0xFF;	
	}
	msgOut->data[CANMSG_SERVO] = controls->sliderR.percent;
	msgOut->data[CANMSG_MOTOR] = controls->jsX.percent;
	char c[5];
	
	oled_print(c, 6, 0);
	msgOut->length = CANMSG_LEN;
	msgOut->id = 0b00100000001;
	msgOut->priority = 2;
	return 0;
}
