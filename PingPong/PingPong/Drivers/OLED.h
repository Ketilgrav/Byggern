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
void OLED_home();
void OLED_goto_line(uint8_t line);
void OLED_pos(uint8_t row,uint8_t column);

#define OLED_DATA *((volatile char*)0x1200)
#define OLED_CONTROL *((volatile char*)0x1000)

#define OLED_MEM_BEGIN 0x1c00
#define OLED_NEXT_LINE 128
#define OLDE_MEM_END 0x1FFF

#define FONT_WIDTH 8
#define OLED_MEM_LINE(linenr) *((volatile char*)(OLED_MEM_BEGIN+linenr*OLED_NEXT_LINE))
#define OLED_MEM_LINE_LOC(line, byte, bit) *((volatile char*)(OLED_MEM_BEGIN+line*OLED_NEXT_LINE+byte*FONT_WIDTH+bit))


void OLED_print_char(char ch, uint8_t line,uint8_t loc);
void OLED_print(char tekst[], uint8_t lineNr, uint8_t charStartPoint);
void OLED_clear();
void OLED_update_screen();



#endif /* OLED_H_ */