/*
 * Game.c
 *
 * Created: 25.09.2015 16:51:47
 *  Author: sverrevr
 */ 

#include "Game.h"
uint8_t runGame(GameState* gameState, Controls* controls, CAN_message* msgMtor, CAN_message* msgPoint){
	oled_clear();
	oled_print("SPILLET KJORER", 3, 0);
	char a[5];
	sprintf(a, "%i", controls->jsX.percent);
	char b[5];
	sprintf(b, "%i", controls->jsY.percent);
	oled_print(a, 4, 0);
	oled_print(b, 5, 0);
	
	if(msgMtor->length == 0){
		msgMtor->data[CANMSG_BTNR_BYTE] &= ~(1<<CANMSG_BTNR_BIT);
	}
	if(controls->btnR.edge){
		msgMtor->data[CANMSG_BTNR_BYTE] |= 1<<CANMSG_BTNR_BIT;
	}
	msgMtor->data[CANMSG_SLIDERR_BYTE] = controls->sliderR.percent;
	msgMtor->data[CANMSG_JSX_BYTE] = controls->jsX.percent;
	msgMtor->length = CANMSG_MOTORSIGNAL_LEN;
	
	if(msgPoint->length && msgPoint->data[CANMSG_PACKAGESPECIFIER] == PACKAGESPECIFIER_GAMEPOINT){
		gameState->points++;
		msgPoint->length = 0;
	}
	char c[5];
	sprintf(c, "%u", gameState->points);
	oled_print(c, 6, 0);
	
	return 0;
}
