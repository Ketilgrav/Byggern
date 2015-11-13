#ifndef OLED_H_
#define OLED_H_

#include <avr/io.h>
#include <util/delay.h>

void oled_init(void);
void oled_home(void);
void oled_line(uint8_t line);
void oled_clear_line(void);
void oled_pos(uint8_t row, uint8_t column);
void oled_draw_line(void);
void oled_print(char* data);
void oled_print_char(uint8_t* character);

#endif
