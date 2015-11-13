#include "oled.h"
#include "characters.h"

volatile uint8_t* OLED_CMD = (uint8_t*)0x8000;
volatile uint8_t* OLED_DATA = (uint8_t*)0x8200;
	
void oled_init(void)
{
	XMCRA |= (1<<SRE)|(1<<SRW11)|(1<<SRW10);
	XMCRB |= (1<<XMM2)|(1<<XMM1)|(0<<XMM0)|(0<<XMBK);

	PORTA = 0xFF;
	PORTC |= (1<<0)|(1<<1);

	_delay_ms(1);

	OLED_CMD[0] = 0xAE;

	OLED_CMD[0] = 0xA1;

	OLED_CMD[0] = 0xDA;
	OLED_CMD[0] = 0x12;

	OLED_CMD[0] = 0xC8;

	OLED_CMD[0] = 0xA8;
	OLED_CMD[0] = 0x3F;

	OLED_CMD[0] = 0xD5;
	OLED_CMD[0] = 0x80;

	OLED_CMD[0] = 0x81;
	OLED_CMD[0] = 0x50;

	OLED_CMD[0] = 0xD9;
	OLED_CMD[0] = 0x21;

	OLED_CMD[0] = 0x20;
	OLED_CMD[0] = 0x00;

	OLED_CMD[0] = 0x21;
	OLED_CMD[0] = 0;
	OLED_CMD[0] = 127;

	OLED_CMD[0] = 0x22;
	OLED_CMD[0] = 0;
	OLED_CMD[0] = 7;

	OLED_CMD[0] = 0xDB;
	OLED_CMD[0] = 0x30;

	OLED_CMD[0] = 0xAD;
	OLED_CMD[0] = 0x00;

	OLED_CMD[0] = 0xA4;

	OLED_CMD[0] = 0xA6;

	OLED_CMD[0] = 0xAF;
	
	uint8_t i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 128; j++)
		{
			OLED_DATA[0] = 0x00;
		}
	}
}

void oled_home(void)
{
	OLED_CMD[0] = 0x21;
	OLED_CMD[0] = 0;
	OLED_CMD[0] = 127;

	OLED_CMD[0] = 0x22;
	OLED_CMD[0] = 0;
	OLED_CMD[0] = 7;
}

void oled_line(uint8_t line)
{
	OLED_CMD[0] = 0x21;
	OLED_CMD[0] = 0;
	OLED_CMD[0] = 127;

	OLED_CMD[0] = 0x22;
	OLED_CMD[0] = line;
	OLED_CMD[0] = line;
}

void oled_clear_line(void)
{
	uint8_t i;
	for (i = 0; i < 128; i++)
		OLED_DATA[0] = 0;
}

void oled_pos(uint8_t row, uint8_t column)
{
	OLED_CMD[0] = 0x21;
	OLED_CMD[0] = column;
	OLED_CMD[0] = column;

	OLED_CMD[0] = 0x22;
	OLED_CMD[0] = row;
	OLED_CMD[0] = row;
}

void oled_draw_line(void)
{
	OLED_DATA[0] = 0xFF;
}

void oled_print(char* data)
{
	uint8_t i = 0;
	while(data[i] != 0)
		oled_print_char(ascii[(uint8_t)data[i++]]);
}

void oled_print_char(uint8_t* character)
{
	uint8_t i;
	OLED_DATA[0] = 0x00;
	_delay_us(10);
	for (i = 0; i < 5; i++)
	{
		OLED_DATA[0] = character[i];
			_delay_us(1);
	}
}
