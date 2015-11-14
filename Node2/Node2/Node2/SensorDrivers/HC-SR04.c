/*
 * HC_SR04.c
 *
 * Created: 14.11.2015 14:23:44
 *  Author: sverrevr
 */ 

#include "HC-SR04.h"

void HCSR04_inti(){
	//porter
	set_bit(HCSR04_TRIG_DDR,HCSR04_TRIG_BIT);
	clear_bit(HCSR04_ECHO_DDR,HCSR04_ECHO_BIT);
	//trenger en timer
	TCCR3B |= 0b11<<CS30;//Ingen prescaler
	TIMSK3 |= TOIE3; //Owerflow interupt enable
}

//Returnerer 58*cm
uint16_t HCSR04_measure(){
	//if timer < 40ms return.
	if(TCNT3 < 16000/(64*40) && !(TIFR3 & TOV3)){
		return;
	}
	
	set_bit(HCSR04_TRIG_PORT,HCSR04_TRIG_BIT);
	_delay_us(HCSR04_TRIGGERPULSEWIDTH_us);
	clear_bit(HCSR04_TRIG_PORT,HCSR04_TRIG_BIT);
	
	TCNT3 = 0;		//resetter timer
	TIFR3 |= TOV3;	//resetter overlow interupt
	while(!read_bit(HCSR04_ECHO_PIN,HCSR04_ECHO_BIT)){
		if(TIFR3 & TOV3){ //if overflow
			return 0;
		}
	}
	
	TCNT3 = 0;		//resetter timer
	while (read_bit(HCSR04_ECHO_PIN,HCSR04_ECHO_BIT)){
		if(TIFR3 & TOV3){ //if overflow
			return 0;
		}
	}
	
	return TCNT3* (64/16);
}

void HCSR04_update_ref(HCSR04_data* data){
	uint16_t time = HCSR04_measure();
	if(time > HCSR04_MAX_TIME || time<HCSR04_MIN_TIME){
		return;
	}
	uint16_t sum = 0;
	data->mesurements[data->queuePointer] = time;
	for(uint8_t i = 0; i < HCSR04_averagingPeriod; ++i){
		sum += data->mesurements[i];
	}
	data->pos_ref = (sum * HCSR04_SCALER / HCSR04_averagingPeriod) - HCSR04_ZERO_POINT;
	data->queuePointer++;
	if(data->queuePointer >= HCSR04_averagingPeriod){
		data->queuePointer = 0;
	}
}