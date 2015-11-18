/*
 * adc.h
 *
 * Created: 23.10.2015 15:57:04
 *  Author: sverrevr
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init();

#define ADC_DDR DDRF
#define SDC_BIT PF1

#define ADC_AVERAGING_PERIOD 50
#define ADC_BOOL_BORDER_VAL 50

//Prescaler can be up to 7
#define ADC_PRESCALER 1

#define ADC_START (ADCSRA |= (1<<ADSC))

typedef struct ADC_signal{
	uint8_t nrMeasurements;
	uint16_t sumValue;		//Tåler ca 100 målinger
	uint8_t boolState;
	uint8_t edge;
	uint8_t count;
}ADC_signal;

uint16_t adc_measure(ADC_signal* signal);
#endif /* ADC_H_ */