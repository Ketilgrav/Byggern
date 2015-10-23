/*
 * HighScore.c
 *
 * Created: 25.09.2015 16:54:43
 *  Author: sverrevr
 */ 

#include "HighScore.h"

uint8_t displayHighScore(JoyStick* js){
	oled_mem_clear();
	oled_mem_print("Highscore",0,0);
	oled_mem_print("  Per: 1024",2,0);
	
	if(js->x_descreet_edge < 0){
		return 1;
	}
	return 0;
}