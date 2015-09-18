/*
 * OLED.h
 *
 * Created: 18.09.2015 10:52:38
 *  Author: sverrevr
 */ 


#ifndef OLED_H_
#define OLED_H_
#include "../MainInclude/MainInclude.h"

void OLED_init();
void oled_home();
void oled_goto_line(uint8_t line);
void oled_clear_line(uint8_t line);
void oled_pos(uint8_t row,uint8_t column);
void oled_print(char* tekst);

#define oled_data *((volatile char*)0x1200)
#define oled_controll *((volatile char*)0x1000)



#endif /* OLED_H_ */