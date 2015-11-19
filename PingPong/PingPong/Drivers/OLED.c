/*
 * OLED.c
 *
 * Created: 18.09.2015 10:52:29
 *  Author: sverrevr
 */ 
#include "OLED.h"


//Fra minnet 1C00 til 1FFF

void OLED_init(){
	/*Seting up the OLED*/
	OLED_CONTROL = 0xae;	 //Display off (0xaf == on)
	
	OLED_CONTROL = 0xa1;    //segment remap (Writes left->right)
	
	OLED_CONTROL = 0xda;	//common pads hardware: alternative
	OLED_CONTROL = 0x12;	//0x32 = 0b11, 0x12 = 0b01, 0x02 = 0b00, 0x22 = 0b10
	
	OLED_CONTROL = 0xc8;    //common output scan direction:com63~com0 (0xc0: writes upwards, 0xc8 writes down)
	
	OLED_CONTROL = 0xa8;    //multiplex ration mode:
	OLED_CONTROL = 0x3f;	//63
	
	OLED_CONTROL = 0xd5;    //display divide ratio/osc. freq. mode
	OLED_CONTROL = 0x80;
	
	OLED_CONTROL = 0x81;	//Change contrast to:
	OLED_CONTROL = 0x50;	//This
		
	OLED_CONTROL = 0xd9;    //Set pre-charge period
	OLED_CONTROL = 0x21;
	
	OLED_CONTROL = 0x20;	//Set Memory Addressing Mode
	OLED_CONTROL = 0x00;	//0x00: Horizontal adressing mode, 0x01 Vertical, 0x02 Page, 0x03 Invalid
	
	OLED_CONTROL = 0xdb;    //VCOM deselect level mode
	OLED_CONTROL = 0x30;
	
	OLED_CONTROL = 0xad;    //Master configuration
	OLED_CONTROL = 0x00;
	
	OLED_CONTROL = 0xa4;    //Out follows RAM content (a5 = all leds are emitting)
	
	OLED_CONTROL = 0xa6;    //set normal display (a7 = invert)
	
	
	OLED_CONTROL = 0x21;	//Start and stop location on line
	OLED_CONTROL = 0x00;	//From start
	OLED_CONTROL = 0xFF;	//Till end
	
	OLED_CONTROL = 0x22;	//Start and stop line
	OLED_CONTROL = 0x00;	//From start
	OLED_CONTROL = 0xFF;	//TO stop
	
	
	OLED_CONTROL = 0x40;	//Last hexsign decides how much the tekst is moved up or down. One value per bit up.
		
	OLED_CONTROL = 0x20;	//Set Memory Addressing Mode
	OLED_CONTROL = 0x00;	//0x00: Horizontal adressing mode, 0x01 Vertical, 0x02 Page, 0x03 Invalid
	
	OLED_CONTROL = 0xB0;	//Starts at first line
	OLED_CONTROL = 0x00;	//LSB of startpoint
	OLED_CONTROL = 0x10;	//MSB of startpoint (Can change last hex sign from 0 to F)
	
//  	OLED_clear();
// 	OLED_update_screen();
 	
	OLED_CONTROL = 0xaf;    // display on
}

void OLED_home(){
	OLED_CONTROL = 0xB0;	//Starts at first line
	OLED_CONTROL = 0x00;	//LSB of startpoint
	OLED_CONTROL = 0x10;	//MSB of startpoint (Can change last hex sign from 0 to F)
}

void OLED_goto_line(uint8_t line){
	if(line > 0xF) line = 0xF;
	OLED_CONTROL = 0xB0 | (line%8);	//Starts at specified line
	OLED_CONTROL = 0x00;			//LSB of startpoint
	OLED_CONTROL = 0x10;			//MSB of startpoint (Can change last hex sign from 0 to F)
}

void OLED_moveRight(uint8_t lsb, uint8_t msb){
	OLED_CONTROL = 0x00|lsb;
	OLED_CONTROL = 0x10|msb;
}

void OLED_pos(uint8_t row,uint8_t column){
	OLED_CONTROL = 0xB0 | (row%8);			//Sett line
	OLED_CONTROL = 0x00 | (column%0x10);	//Sett lsb col
	OLED_CONTROL = 0x10 | (column / 0x10);	//Sett msb col
}


/*Print a text string at specified line and byte starting point
Line can be from 0 to 8, starting point from 0 to 16
The character '-', followed by '<','V','^', '>' creates arrows
The character '-' followed by 's' creates a 2byte long space invader.*/
void OLED_print(char tekst[], uint8_t lineNr, uint8_t charStartPoint){
	if(lineNr > 7){
		lineNr = 7;
	}
	for(uint8_t textLoc = 0, printLoc = charStartPoint; tekst[textLoc] != '\0' && printLoc < 16; ++textLoc, ++printLoc){
		if(tekst[textLoc] == '-'){
			switch(tekst[textLoc+1]){
				case '^':
				OLED_print_char(127, lineNr, printLoc);
				textLoc++;
				break;
				case 'v':
				OLED_print_char(128, lineNr, printLoc);
				textLoc++;
				break;
				case '<':
				OLED_print_char(129, lineNr, printLoc);
				textLoc++;
				break;
				case '>':
				OLED_print_char(130, lineNr, printLoc);
				textLoc++;
				break;
				case 's':
				OLED_print_char(131, lineNr, printLoc);
				printLoc++;
				textLoc++;
				OLED_print_char(132, lineNr, printLoc);
				break;
				default:
				OLED_print_char('-', lineNr, printLoc);
				break;
				
			}
		}
		else{
			OLED_print_char(tekst[textLoc], lineNr, printLoc);
		}
	}
}


void OLED_print_char(char ch, uint8_t line, uint8_t loc){
	for(uint8_t j = 0; j<8; ++j){
		OLED_MEM_LINE_LOC(line, loc, j) = pgm_read_byte(&font[ch-asciiOffset][j]);
	}
}

/*Sets the value 0 at all memory locations used by the OLED*/
void OLED_clear(){
	volatile char* memBegin = OLED_MEM_BEGIN;
	for(uint16_t i = 0; i < 1024; ++i){
		*(memBegin+i) = 0x00;
	}
}


void OLED_update_screen(){
	OLED_goto_line(0);
	volatile char* memBegin = OLED_MEM_BEGIN;
	for(uint16_t i = 0; i < 1024; ++i){
		OLED_DATA = *(memBegin+i);
	}
}