/*
 * Font.h
 *
 * Created: 18.09.2015 14:26:52
 *  Author: sverrevr
 */ 


#ifndef FONT_H_
#define FONT_H_

#include <avr/pgmspace.h>
#define asciiOffset ' '
#define FONT_SIZE 101
extern const unsigned char PROGMEM font[FONT_SIZE][8];


#endif /* FONT_H_ */