/*
 * OLED.c
 *
 * Created: 18.09.2015 10:52:29
 *  Author: sverrevr
 */ 
#include "OLED.h"


void OLED_init(){	
	oled_control = 0xae;	 //Display off (0xaf == on)
	
	oled_control = 0xa1;    //segment remap (Skrive v->h)
	
	oled_control = 0xda;	//common pads hardware: alternative
	oled_control = 0x12;	//0x32 = 0b11, 0x12 = 0b01, 0x02 = 0b00, 0x22 = 0b10
	
	oled_control = 0xc8;    //common output scan direction:com63~com0 (skriver oppover(c0) eller nedover(c8))
	
	oled_control = 0xa8;    //multiplex ration mode:
	oled_control = 0x3f;	//63
	
	oled_control = 0xd5;    //display divide ratio/osc. freq. mode
	oled_control = 0x80;
	
	oled_control = 0x81;   //Endre kontrast til:
	oled_control = 0x50;	//Dette
		
	oled_control = 0xd9;    //set pre-charge period
	oled_control = 0x21;
	
	oled_control = 0x20;	//Set Memory Addressing Mode
	oled_control = 0x00;	//0x00: Horizontal adressing mode, 0x01 Vertical, 0x02 Page, 0x03 Invalid
	
	oled_control = 0xdb;    //VCOM deselect level mode
	oled_control = 0x30;
	
	oled_control = 0xad;    //master configuration
	oled_control = 0x00;
	
	oled_control = 0xa4;    //out follows RAM content (a5 = alle led lyser)
	
	oled_control = 0xa6;    //set normal display (a7 = invert)
		
	
	oled_control = 0xaf;    // display on
	
	
	oled_control = 0x21;	//Hvor man begynner og slutter på en linje
	oled_control = 0x00;	//Fra start
	oled_control = 0xFF;	//Til slutt
	
	oled_control = 0x22;	//Hvor man begynner og slutter opp go ned
	oled_control = 0x00;	//Fra start
	oled_control = 0xFF;	//Til slutt
	
	
	oled_control = 0x40;	//Siste hextegn bestemmer hvor mye teksten flyttes opp, en verdi per bit opp. Funker ikke å endre underveis i koden?
	
	//Tømmer skjermen
	for(unsigned int i = 0; i < 1024; ++i){
		oled_data = 0b00000000;
	}
	
	
	oled_control = 0x20;	//Set Memory Addressing Mode
	oled_control = 0x00;	//0x00: Horizontal adressing mode, 0x01 Vertical, 0x02 Page, 0x03 Invalid
	
	
	oled_control = 0xB0;	//Begynner på første linje
	oled_control = 0x00;	//LSB til startpunkt
	oled_control = 0x10;	//MSB til startbit (bortover) (så hvilken kolonne) (Kan endre siste hex tegnet fra 0 til F)
	
	
	//oled_data = 0b11000111;
	
	//printf("OLED initd\n\r");
}

void oled_home(){
	oled_control = 0xB0;	//Begynner på første linje
	oled_control = 0x00;	//LSB til startpunkt
	oled_control = 0x10;	//MSB til startbit (bortover) (så hvilken kolonne) (Kan endre siste hex tegnet fra 0 til F)
}

void oled_goto_line(uint8_t line){
	oled_control = 0xB0 | (line%8);	//Begynner på første linje
	oled_control = 0x00;	//LSB til startpunkt
	oled_control = 0x10;	//MSB til startbit (bortover) (så hvilken kolonne) (Kan endre siste hex tegnet fra 0 til F)
}

void oled_moveRight(uint8_t lsb, uint8_t msb){
	oled_control = 0x00|lsb;
	oled_control = 0x10|msb;
}

void oled_clear_line(uint8_t line){
	oled_goto_line(line);
	for(uint8_t i = 0; i<128; ++i){
		oled_print(" ");
	}
	oled_goto_line(line);
}

void oled_pos(uint8_t row,uint8_t column){
	oled_control = 0xB0 | (row%8);			//Sett Linje
	oled_control = 0x00 | (column%0x10);	//Sett lsb kolonne
	oled_control = 0x10 | (column / 0x10);	//Sett msb kolonne
}

void oled_print(char tekst[]){
	//Må trekke fra 32 for å slå opp i font.
	for(uint8_t i = 0; tekst[i] != '\0' && i<16; ++i){
		if(tekst[i] == '-'){
			switch(tekst[i+1]){
				case '^':
					oled_print_char(127);
					i++;
					break;
				case 'v':
					oled_print_char(128);
					i++;
					break;
				case '<':
					oled_print_char(129);
					i++;
					break;
				case '>':
					oled_print_char(130);
					i++;
					break;
				case 's':
					oled_print_char(131);
					oled_print_char(132);
					i++;
					break;
				default:
					oled_print_char('-');
					break;
					
			}
		}
		else{
			oled_print_char(tekst[i]);	
		}
	}
}

void oled_print_char(char ch){
	//Må trekke fra 32 for å slå opp i font.
	for(int j = 0; j<8; ++j){
		oled_data = pgm_read_byte(&font[ch-asciiOffset][j]);
	}
}

void oled_clear_screen(){
	for(int i=0; i< 8; ++i){
		oled_clear_line(i);
	}
}