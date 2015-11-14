/*
 * HighScore.c
 *
 * Created: 25.09.2015 16:54:43
 *  Author: sverrevr
 */ 

#include "HighScore.h"

uint8_t displayHighScore(Controls* control){
	oled_clear();
	oled_print("Highscore",0,0);
	oled_print("  Per: 1024",2,0);
	
	if(control->jsX.descreet_edge < 0){
		return 1;
	}
	return 0;
}