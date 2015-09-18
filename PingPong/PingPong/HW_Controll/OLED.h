/*
 * OLED.h
 *
 * Created: 18.09.2015 10:52:38
 *  Author: sverrevr
 */ 


#ifndef OLED_H_
#define OLED_H_
#include "../MainInclude/MainInclude.h"

void oled_init();
void oled_home();
void oled_goto_line(uint8_t line);
void oled_clear_line(uint8_t line);
void oled_pos(uint8_t row,uint8_t column);
void oled_print(char* tekst);




#endif /* OLED_H_ */