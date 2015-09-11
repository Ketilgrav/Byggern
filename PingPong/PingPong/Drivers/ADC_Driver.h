/*
 * ADC_Driver.h
 *
 * Created: 11.09.2015 11:15:23
 *  Author: sverrevr
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#define INTR_DDR DDRB
#define INTR_PORT PORTB
#define INTR_PIN PINB
#define INTR_bit PB1
#define ADC_memory_adress 0x1400 //Sjekk om rett
#define ADC_single_ended 0b0100

int ADC_read_convertion(volatile int* ADC_memory);
int ADC_convert(int channel);
int ADC_init();

#endif /* ADC_DRIVER_H_ */