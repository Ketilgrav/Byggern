/*
 * adc.c
 *
 * Created: 23.10.2015 15:56:56
 *  Author: sverrevr
 */ 
#include "../MainInclude.h"
#include "adc.h"

volatile uint16_t adcVal = 0;
volatile uint8_t adcDoUpdate = 1;

void adc_init(){
	clear_bit(DDRF,PF0);
	
	ADMUX |= (1<<MUX0); //Bruker ADC1
	ADMUX |= (1<<REFS0); //Bruker AVCC som refferanse.
	
	//ADC enable. //Prescaler, bytt ut en med verdier opp til 7. //Aktiverer interupt
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADIE);
	ADCSRB |= (0<<ADTS0); //Free running mode
}


ISR(ADC_vect){
	adcVal = ADC;
	adcDoUpdate = 1;
}


uint16_t adc_measure(ADC_signal* signal){
	if(!adcDoUpdate){
		//If the adc convertion has not finished
		return;
	}
	
	signal->nrMeasurements ++;
	signal->sumValue += adcVal;
	signal->edge = 0;
	
	//Averages out averagingPeriod number of values
	if(signal->nrMeasurements > averagingPeriod){
		if(signal->sumValue / signal->nrMeasurements < boolValueBorder){
			if(signal->boolState != 1){
				signal->count++;
			}
			if(signal->boolState == 0){
				signal->edge = 1;
			}
			signal->boolState = 1;
		}
		else{
			signal->boolState = 0;
		}
		
		signal->nrMeasurements = 0;
		signal->sumValue = 0;
	}
	
	//Starting new convertion
	ADCSRA |= (1<<ADSC);
	adcDoUpdate = 0;
}