/*
 * Game.c
 *
 * Created: 25.09.2015 16:51:47
 *  Author: sverrevr
 */ 
#include "../MainInclude/MainInclude.h"
#include "../Drivers/Controllers.h"

uint8_t runGame(JoyStick* js, Slider* s_l, Slider* s_r){
	oled_goto_line(3);
	oled_print("SPILLET KJORER");
	return 0;
}