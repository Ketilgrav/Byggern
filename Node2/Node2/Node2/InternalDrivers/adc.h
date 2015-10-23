/*
 * adc.h
 *
 * Created: 23.10.2015 15:57:04
 *  Author: sverrevr
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init();
uint16_t adc_getVal();

#define adc_DDR DDRF
#define adc_BIT PF0

#define averagingPeriod 50
#define boolValueBorder 200
typedef struct ADC_signal{
	uint8_t nrMeasurements;
	uint16_t sumValue;		//Tåler ca 100 målinger
	uint8_t boolState;
	uint8_t count;
}ADC_signal;

uint16_t adc_measure(ADC_signal* signal);
#endif /* ADC_H_ */