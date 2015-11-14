/*
 * OLED.h
 *
 * Created: 18.09.2015 10:52:38
 *  Author: sverrevr
 */ 


#ifndef OLED_H_
#define OLED_H_
#include "../MainInclude.h"
#include "../Etc/Font.h"

void OLED_init();
void oled_home();
void oled_goto_line(uint8_t line);
//void oled_clear_line(uint8_t line);
void oled_pos(uint8_t row,uint8_t column);
/*void oled_print(char tekst[]);
void oled_print_char(char ch);
void oled_clear_screen();*/


#define oled_data *((volatile char*)0x1200)
#define oled_control *((volatile char*)0x1000)

#define oled_mem_begin 0x1c00
#define oled_next_line 128
#define oled_mem_end 0x1FFF

#define font_width 8
#define oled_mem_line(linenr) *((volatile char*)(oled_mem_begin+linenr*oled_next_line))
#define oled_mem_line_loc(line, byte, bit) *((volatile char*)(oled_mem_begin+line*oled_next_line+byte*font_width+bit))


void oled_print_char(char ch, uint8_t line,uint8_t loc);
void oled_print(char tekst[], uint8_t lineNr, uint8_t charStartPoint);
void oled_clear();
void oled_update_screen();



#endif /* OLED_H_ */