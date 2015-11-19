/*
 * ADC_Driver.c
 *
 * Created: 11.09.2015 11:15:12
 *  Author: sverrevr
 */ 

#include "ADC_Driver.h"

void ADC_init(){
	clear_bit(INTR_DDR, INTR_BIT);
}

//Channel 0-3. (tilsvarer 1-4 i datablad, 0indekserte dem)
uint8_t ADC_convert(char channel){
	//ch1 = 0100, ch2 = 0101, ch3 = 0110, ch4 = 0111, dette er lsb
	if(channel > 3) channel = 3;
	else if(channel< 0) channel = 0;
	
	*ADC_MEMORY = ADC_SINGLE_ENDED | channel;
	
	//Venter på svar
	while(read_bit(INTR_PIN, INTR_bit));
	
	return *ADC_MEMORY;
	
}

