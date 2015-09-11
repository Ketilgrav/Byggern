/*
 * ADC_Driver.h
 *
 * Created: 11.09.2015 11:15:23
 *  Author: sverrevr
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include "../MainInclude/MainInclude.h"

#define INTR_DDR DDRB
#define INTR_PORT PORTB
#define INTR_PIN PINB
#define INTR_bit PB1
#define ADC_memory ((volatile char*)0x1400)
#define ADC_single_ended 0b0100

uint8_t ADC_convert(char channel);
void ADC_init();

#endif /* ADC_DRIVER_H_ */