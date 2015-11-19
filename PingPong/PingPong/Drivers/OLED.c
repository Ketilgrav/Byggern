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


/*Print a text string at specified line and byte starting point
Line can be from 0 to 8, starting point from 0 to 16
The character '-', followed by '<','V','^', '>' creates arrows
The character '-' followed by 's' creates a 2byte long space invader.*/
void oled_print(char tekst[], uint8_t lineNr, uint8_t charStartPoint){
	if(lineNr > 7){
		lineNr = 7;
	}
	for(uint8_t textLoc = 0, printLoc = 0; tekst[textLoc] != '\0' && printLoc < 16-charStartPoint; ++textLoc, ++printLoc){
		if(tekst[printLoc] == '-'){
			switch(tekst[printLoc+1]){
				case '^':
				oled_print_char(127, lineNr, printLoc+charStartPoint);
				textLoc++;
				break;
				case 'v':
				oled_print_char(128, lineNr, printLoc+charStartPoint);
				textLoc++;
				break;
				case '<':
				oled_print_char(129, lineNr, printLoc+charStartPoint);
				textLoc++;
				break;
				case '>':
				oled_print_char(130, lineNr, printLoc+charStartPoint);
				textLoc++;
				break;
				case 's':
				oled_print_char(131, lineNr, printLoc+charStartPoint);
				printLoc++;
				textLoc++;
				oled_print_char(132, lineNr, printLoc+charStartPoint);
				break;
				default:
				oled_print_char('-', lineNr, printLoc+charStartPoint);
				break;
				
			}
		}
		else{
			oled_print_char(tekst[textLoc], lineNr, printLoc+charStartPoint);
		}
	}
}


void oled_print_char(char ch, uint8_t line, uint8_t loc){
	for(int j = 0; j<8; ++j){
		oled_mem_line_loc(line, loc, j) = pgm_read_byte(&font[ch-asciiOffset][j]);
	}
}

/*Sets the value 0 at all memory locations used by the oled*/
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