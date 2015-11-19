/*
 * OLED.c
 *
 * Created: 18.09.2015 10:52:29
 *  Author: sverrevr
 */ 
#include "OLED.h"


//Fra minnet 1C00 til 1FFF

void OLED_init(){
	/*Seting up the oled*/
	oled_control = 0xae;	 //Display off (0xaf == on)
	
	oled_control = 0xa1;    //segment remap (Writes left->right)
	
	oled_control = 0xda;	//common pads hardware: alternative
	oled_control = 0x12;	//0x32 = 0b11, 0x12 = 0b01, 0x02 = 0b00, 0x22 = 0b10
	
	oled_control = 0xc8;    //common output scan direction:com63~com0 (0xc0: writes upwards, 0xc8 writes down)
	
	oled_control = 0xa8;    //multiplex ration mode:
	oled_control = 0x3f;	//63
	
	oled_control = 0xd5;    //display divide ratio/osc. freq. mode
	oled_control = 0x80;
	
	oled_control = 0x81;	//Change contrast to:
	oled_control = 0x50;	//This
		
	oled_control = 0xd9;    //Set pre-charge period
	oled_control = 0x21;
	
	oled_control = 0x20;	//Set Memory Addressing Mode
	oled_control = 0x00;	//0x00: Horizontal adressing mode, 0x01 Vertical, 0x02 Page, 0x03 Invalid
	
	oled_control = 0xdb;    //VCOM deselect level mode
	oled_control = 0x30;
	
	oled_control = 0xad;    //Master configuration
	oled_control = 0x00;
	
	oled_control = 0xa4;    //Out follows RAM content (a5 = all leds are emitting)
	
	oled_control = 0xa6;    //set normal display (a7 = invert)
	
	
	oled_control = 0x21;	//Start and stop location on line
	oled_control = 0x00;	//From start
	oled_control = 0xFF;	//Till end
	
	oled_control = 0x22;	//Start and stop line
	oled_control = 0x00;	//From start
	oled_control = 0xFF;	//TO stop
	
	
	oled_control = 0x40;	//Last hexsign decides how much the tekst is moved up or down. One value per bit up.
		
	oled_control = 0x20;	//Set Memory Addressing Mode
	oled_control = 0x00;	//0x00: Horizontal adressing mode, 0x01 Vertical, 0x02 Page, 0x03 Invalid
	
	oled_control = 0xB0;	//Starts at first line
	oled_control = 0x00;	//LSB of startpoint
	oled_control = 0x10;	//MSB of startpoint (Can change last hex sign from 0 to F)
	
	oled_clear();
	oled_update_screen();
	
	oled_control = 0xaf;    // display on
}

void oled_home(){
	oled_control = 0xB0;	//Starts at first line
	oled_control = 0x00;	//LSB of startpoint
	oled_control = 0x10;	//MSB of startpoint (Can change last hex sign from 0 to F)
}

void oled_goto_line(uint8_t line){
	if(line > 0xF) line = OxF;
	oled_control = 0xB0 | (line%8);	//Starts at specified line
	oled_control = 0x00;			//LSB of startpoint
	oled_control = 0x10;			//MSB of startpoint (Can change last hex sign from 0 to F)

void oled_moveRight(uint8_t lsb, uint8_t msb){
	oled_control = 0x00|lsb;
	oled_control = 0x10|msb;
}

void oled_pos(uint8_t row,uint8_t column){
	oled_control = 0xB0 | (row%8);			//Sett line
	oled_control = 0x00 | (column%0x10);	//Sett lsb col
	oled_control = 0x10 | (column / 0x10);	//Sett msb col
}

void oled_print(char tekst[], uint8_t lineNr, uint8_t charStartPoint){
	if(lineNr > 7){
		lineNr = 7;
	}
	
	//Må trekke fra 32 for å slå opp i font.
	for(uint8_t i = 0; tekst[i] != '\0' && i < 16-charStartPoint; ++i){
		if(tekst[i] == '-'){
			switch(tekst[i+1]){
				case '^':
				oled_print_char(127, lineNr, i+charStartPoint);
				i++;
				break;
				case 'v':
				oled_print_char(128, lineNr, i+charStartPoint);
				i++;
				break;
				case '<':
				oled_print_char(129, lineNr, i+charStartPoint);
				i++;
				break;
				case '>':
				oled_print_char(130, lineNr, i+charStartPoint);
				i++;
				break;
				case 's':
				oled_print_char(131, lineNr, i+charStartPoint);
				i++;
				oled_print_char(132, lineNr, i+charStartPoint);
				break;
				default:
				oled_print_char('-', lineNr, i+charStartPoint);
				break;
				
			}
		}
		else{
			oled_print_char(tekst[i], lineNr, i+charStartPoint);
		}
	}
}

void oled_print_char(char ch, uint8_t line, uint8_t loc){
	//Må trekke fra 32 for å slå opp i font.
	for(int j = 0; j<8; ++j){
		oled_mem_line_loc(line, loc, j) = pgm_read_byte(&font[ch-asciiOffset][j]);
	}
}

void oled_clear(){
	volatile char* memBegin = oled_mem_begin;
	for(unsigned int i = 0; i < 1024; ++i){
		*(memBegin+i) = 0x00;
	}
}


void oled_update_screen(){
	oled_goto_line(0);
	volatile char* memBegin = oled_mem_begin;
	for(unsigned int i = 0; i < 1024; ++i){
		oled_data = *(memBegin+i);
	}
}