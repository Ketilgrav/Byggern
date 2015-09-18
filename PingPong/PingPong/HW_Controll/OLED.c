/*
 * OLED.c
 *
 * Created: 18.09.2015 10:52:29
 *  Author: sverrevr
 */ 
#include "OLED.h"

void OLED_init(){	
	oled_controll = 0xae;	 //Display off (0xaf == on)
	
	oled_controll = 0xa1;    //segment remap (Skrive v->h)
	
	oled_controll = 0xda;	//common pads hardware: alternative
	oled_controll = 0x12;	//0x32 = 0b11, 0x12 = 0b01, 0x02 = 0b00, 0x22 = 0b10
	
	oled_controll = 0xc8;    //common output scan direction:com63~com0 (skriver oppover(c0) eller nedover(c8))
	
	oled_controll = 0xa8;    //multiplex ration mode:
	oled_controll = 0x3f;	//63
	
	oled_controll = 0xd5;    //display divide ratio/osc. freq. mode
	oled_controll = 0x80;
	
	oled_controll = 0x81;   //Endre kontrast til:
	oled_controll = 0x50;	//Dette
		
	oled_controll = 0xd9;    //set pre-charge period
	oled_controll = 0x21;
	
	oled_controll = 0x20;	//Set Memory Addressing Mode
	oled_controll = 0x00;	//0x00: Horizontal adressing mode, 0x01 Vertical, 0x02 Page, 0x03 Invalid
	
	oled_controll = 0xdb;    //VCOM deselect level mode
	oled_controll = 0x30;
	
	oled_controll = 0xad;    //master configuration
	oled_controll = 0x00;
	
	oled_controll = 0xa4;    //out follows RAM content (a5 = alle led lyser)
	
	oled_controll = 0xa6;    //set normal display (a7 = invert)
		
	
	oled_controll = 0xaf;    // display on
	
	
	oled_controll = 0x21;	//Hvor man begynner og slutter på en linje
	oled_controll = 0x00;	//Fra start
	oled_controll = 0xFF;	//Til slutt
	
	oled_controll = 0x22;	//Hvor man begynner og slutter opp go ned
	oled_controll = 0x00;	//Fra start
	oled_controll = 0xFF;	//Til slutt
	
	oled_controll = 0x00;	//LSB til startpunkt
	oled_controll = 0x10;	//MSB til startbit (bortover) (så hvilken kolonne) (Kan endre siste hex tegnet fra 0 til F)
	
	oled_controll = 0x40;	//Siste hextegn bestemmer hvor mye teksten flyttes opp, en verdi per bit opp. Funker ikke å endre underveis i koden?
	
	//Tømmer skjermen
	for(int i = 0; i < 1024; ++i){
		oled_data = 0b00000000;
	}
	
	
	oled_controll = 0x20;	//Set Memory Addressing Mode
	oled_controll = 0x02;	//0x00: Horizontal adressing mode, 0x01 Vertical, 0x02 Page, 0x03 Invalid
	
	
	
	
	//oled_data = 0b11000111;
	
	puts("OLED init'd\n\r");
}

void oled_home(){
	
}

void oled_goto_line(uint8_t line){
	
}

void oled_clear_line(uint8_t line){
	
}

void oled_pos(uint8_t row,uint8_t column){
	
}

void oled_print(char* tekst){
	
}