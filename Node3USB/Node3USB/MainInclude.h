/*
 * MainInclude.h
 *
 * Created: 10.11.2015 09:35:52
 *  Author: sverrevr
 */ 


#ifndef MAININCLUDE_H_
#define MAININCLUDE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#define set_bit( reg, bit ) (reg |= (1<<bit))
#define clear_bit( reg, bit) (reg &= ~(1<<bit))
#define toggle_bit( reg, bit) (reg ^= (1<<bit))
#define read_bit( reg, bit ) (reg & (1<<bit))
#define wait_until_bit_is_set( reg, bit) while( !read_bit(reg, bit))
#define wait_until_bit_is_cleared(reg, bit) while( test_bit(reg, bit))

#include <stdio.h>
#include <string.h>

#endif /* MAININCLUDE_H_ */