/*
 * HighScore.c
 *
 * Created: 25.09.2015 16:54:43
 *  Author: sverrevr
 */ 

#include "HighScore.h"

uint8_t displayHighScore(GameState* gameState, Controls* control){
	oled_clear();
	oled_print("Current         ")
	oled_print("      High Score",0,0);
	char pointsString[5]
	sprintf(pointsString, "%u", gameState->points)
	oled_print(pointsString,3,6);
	
	if(control->jsX.descreet_edge < 0){
		return 1;
	}
	return 0;
}