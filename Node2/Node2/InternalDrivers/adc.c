/*
 * adc.c
 *
 * Created: 23.10.2015 15:56:56
 *  Author: sverrevr
 */ 
#include "../MainInclude.h"
#include "adc.h"

void adc_init(){
	clear_bit(DDRF,PF0);
	
	
	ADMUX |= (1<<MUX0); //Bruker ADC1
	ADMUX |= (1<<REFS0); //Bruker AVCC som refferanse.
	
	//ADC enable. //Prescaler, bytt ut en med verdier opp til 7. //Aktiverer interupt
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADIE);
	ADCSRB |= (0<<ADTS0); //Free running mode
}

uint16_t adc_getVal(){
	//Starter konvertering
	ADCSRA |= (1<<ADSC);
	while(! (ADCSRA & ADIF)) //Så lenge konverteringa ikke er ferdig
	ADCSRA |= ADIF; //Resetter interupten
	return ADC;
}


uint16_t adc_measure(ADC_signal* signal){
	signal->nrMeasurements ++;
	signal->sumValue += adc_getVal();
	signal->edge = 0;
	
	if(signal->nrMeasurements > averagingPeriod){
		if(signal->sumValue / signal->nrMeasurements < boolValueBorder){
			//printf("%u  \r",signal->sumValue / signal->nrMeasurements);
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
}