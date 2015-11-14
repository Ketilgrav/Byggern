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
	TCCR3B |= 1<<CS30;//Ingen prescaler
}

//Returnerer 58*cm
uint8_t HCSR04_measure(){
	set_bit(HCSR04_TRIG_PORT,HCSR04_TRIG_BIT);
	_delay_us(HCSR04_TRIGGERPULSEWIDTH_us);
	wait_until_bit_is_set(HCSR04_ECHO_PIN,HCSR04_ECHO_BIT);
	TCNT3 = 0;
	wait_until_bit_is_cleared(HCSR04_ECHO_PIN,HCSR04_ECHO_PIN);
	uint8_t time = TCNT3;
	return time;
}

void HCSR04_update_ref(uint8_t* posRef){
	uint8_t time = HCSR04_measure();
	if(time > HCSR04_MAX_TIME || time<HCSR04_MIN_TIME){
		return;
	}
	*posRef = HCSR04_ZERO_POINT + posRef*HCSR04_SCALER;
}