/*
 * ADC_Driver.c
 *
 * Created: 11.09.2015 11:15:12
 *  Author: sverrevr
 */ 

#include "ADC_Driver.h"
#include "../MainInclude/MainInclude.h"


//Channel 0-3. (tillsvarer 1-4 i datablad, 0indekserte dem)
void ADC_start_convertion(volatile int* ADC_memory, int channel){
	*ADC_memory = ADC_single_ended | channel;
}

int ADC_read_convertion(volatile int* ADC_memory){
	return *ADC_memory;
}

int ADC_convert(int channel){
	
	//ch1 = 0100, ch2 = 0101, ch3 = 0110, ch4 = 0111, dette er lsb
	if(channel > 3) channel = 3;
	else if(channel< 0) channel = 0;
	
	volatile int* ADC_memory = ADC_memory_adress;
	
	ADC_start_convertion(ADC_memory,channel);
	
	while(read_bit(INTR_PIN,INTR_bit));
	
	return ADC_read_convertion(ADC_memory);
}

int ADC_init(){
	clear_bit(INTR_DDR,INTR_bit);
}