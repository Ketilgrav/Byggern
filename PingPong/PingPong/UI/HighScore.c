/*
 * HighScore.c
 *
 * Created: 25.09.2015 16:54:43
 *  Author: sverrevr
 */ 

#include "HighScore.h"

uint8_t displayHighScore(GameState* gameState, Controls* control){
	OLED_clear();
	OLED_print("Current         ",0,0);
	OLED_print("      High Score",1,0);
	char pointsString[5];
	sprintf(pointsString, "%u", gameState->record);
	OLED_print(pointsString,3,6);
	OLED_print(gameState->name,4,0);
	
	if(control->jsX.descreet_edge < 0){
		return 1;
	}
	return 0;
}