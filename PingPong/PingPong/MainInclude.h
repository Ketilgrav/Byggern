/*
 * Main_Include.h
 *
 * Created: 28.08.2015 11:32:51
 *  Author: ketilgs
 */ 


#ifndef MAININCLUDE_H_
#define MAININCLUDE_H_

#define F_CPU 4915200UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/eeprom.h>

//IO manipulering
#define set_bit( reg, bit ) (reg |= (1<<bit))
#define clear_bit( reg, bit) (reg &= ~(1<<bit))
#define toggle_bit( reg, bit) (reg ^= (1<<bit))
#define read_bit( reg, bit ) (reg & (1<<bit))
#define wait_until_bit_is_set( reg, bit) while( !read_bit(reg, bit))
#define wait_until_bit_is_cleared(reg, bit) while( test_bit(reg, bit))

#include "Drivers/OLED.h"
#include "../../InterNodeHeaders/CanMessageFormat.h"
#include "../../InterNodeHeaders/canID.h"
#include <string.h>

#define EEPROM_HIGHSCOREBYTE ((uint8_t*)32)
//NB multible bytes are used for the name, see NAME_LEN to find size
#define EEPROM_HIGHSCORENAME ((uint8_t*)33)

typedef enum { false, true} bool;

#endif /* MAININCLUDE_H_ */