/*
 * servo.c
 *
 * Created: 23.10.2015 09:09:19
 *  Author: sverrevr
 */ 
#include "servo.h"
#include "../MainInclude/MainInclude.h"

void servo_init(){
	set_bit(PWM_DDR, PWM_bit);
	
	//Setter fast PWM 9 bit, 0110, WGM10. MAX = 0x01FF
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12)|(1<<WGM13);
	
	//Clear OC1A on compare match, set OC1A at BOTTOM
	TCCR1A |= (1<<COM1A1);
	
	//Clock prescaler
	TCCR1B |= (clock_scaler << CS10);
	
	//TOP signalet
	ICR1 = duty_cycle_ms * F_CPU / clock_scaler_val;
	
	//OC1A er pwm signalet	går ut på PB5
	//OCR1A nivået for sette lav. 
	OCR1A = pulse_width_min * F_CPU / clock_scaler_val;
}

void servo_set(int percent){
	if(percent > 100){
		percent = 100;
	}
	else if(percent < -100){
		percent = -100;		
	}
	OCR1A = (pulse_width_neutral + ((pulse_width_max-pulse_width_min)/200)*percent)* F_CPU / clock_scaler_val;
}