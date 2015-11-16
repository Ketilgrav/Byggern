/*
 * HC_SR04.c
 *
 * Created: 14.11.2015 14:23:44
 *  Author: sverrevr
 */ 

#include "HC-SR04.h"

void HCSR04_inti(){
	//porter
	set_bit(S0_TRIG_DDR,S0_TRIG_BIT);
	clear_bit(S0_ECHO_DDR,S0_ECHO_BIT);
	set_bit(S1_TRIG_DDR,S1_TRIG_BIT);
	clear_bit(S1_ECHO_DDR,S1_ECHO_BIT);
	//trenger en timer
	TCCR0B |= 0b100<<CS00;
	TIMSK0 |= TOIE0; //Owerflow interupt enable
}

//Returnerer 58*cm
uint8_t HCSR04_measure(uint8_t sensorID){
	//if timer < 40ms return.
	if(TCNT0 < 16000/(64*40) && !(TIFR0 & TOV0)){
		//printf("Too fast");
		return 0;
	}
	if (sensorID == SENSOR0){
		set_bit(S0_TRIG_PORT,S0_TRIG_BIT);
		_delay_us(HCSR04_TRIGGERPULSEWIDTH_us);
		clear_bit(S0_TRIG_PORT,S0_TRIG_BIT);
		
		TCNT0 = 0;		//resetter timer
		TIFR0 |= TOV0;	//resetter overlow interupt
		while(!read_bit(S0_ECHO_PIN,S0_ECHO_BIT)){
			if(TIFR0 & TOV0){ //if overflow
				printf("Overflow");
				return 0;
			}
		}
		
		TCNT0 = 0;		//resetter timer
		while (read_bit(S0_ECHO_PIN,S0_ECHO_BIT)){
			if(TIFR0 & TOV0){ //if overflow
				printf("Overflow");
				return 0;
			}
		}
		
		return TCNT0* (HCSR04_PRESCALER/16);
	}
	else if(sensorID == SENSOR1){		
		set_bit(S1_TRIG_PORT,S1_TRIG_BIT);
		_delay_us(HCSR04_TRIGGERPULSEWIDTH_us);
		clear_bit(S1_TRIG_PORT,S1_TRIG_BIT);
		
		TCNT0 = 0;		//resetter timer
		TIFR0 |= TOV0;	//resetter overlow interupt
		while(!read_bit(S1_ECHO_PIN,S1_ECHO_BIT)){
			if(TIFR0 & TOV0){ //if overflow
				printf("Overflow");
				return 0;
			}
		}
		
		TCNT0 = 0;		//resetter timer
		while (read_bit(S1_ECHO_PIN,S1_ECHO_BIT)){
			if(TIFR0 & TOV0){ //if overflow
				printf("Overflow");
				return 0;
			}
		}
		
		return TCNT0;
	}
}

void HCSR04_update_ref(HCSR04_data* data, uint8_t sensorId){
	uint8_t time = HCSR04_measure(sensorId);
	int16_t encoderDist = echo_time_to_encoder_val(time);
	
	//Verdien er utenfor bordet, da ignoreres den
	if(encoderDist>BOARD_SIZE/2 || encoderDist<-BOARD_SIZE/2){
		puts("too far\r\n");
		return;
	}
	
	//Verdien er utenfor standardavviket, da anntaes at det er en feilmåling og den ignoreres.
	if(encoderDist > data->pos_ref+HCSR04_MAX_DEVIATION_ENCODER_DIST || encoderDist < data->pos_ref+HCSR04_MAX_DEVIATION_ENCODER_DIST){
		puts("deviation\r\n");
		return;
	}
		
	data->mesurements[data->queuePointer] = time;
	data->queuePointer++;
	if(data->queuePointer >= HCSR04_averagingPeriod) data->queuePointer = 0;
	
	uint16_t sum = 0;
	for(uint8_t i = 0; i < HCSR04_averagingPeriod; ++i){
		sum += data->mesurements[i];
	}
	
	data->time = sum/HCSR04_averagingPeriod;
	data->pos_ref = echo_time_to_encoder_val(data->time);
	
}

int16_t echo_time_to_encoder_val(uint8_t time){
	uint16_t distanceTime = (time * (HCSR04_PRESCALER/16))	//Avstanden i uS fra sensoren
	uint16_t motorDistanceTime;								//Avstanden i uS fra startpossisjonen til motoren	
	if(distanceTime  <= HCSR04_DIST_FROM_MOTOR0){
		motorDistanceTime = 0;								//Om denne er til venstre for boksen settes den til 0 for å unngå negative verdier, som uansett burde ignoreres siden motoren ikke kan dra hit.
	}
	else{
		motorDistanceTime = (distanceTime - HCSR04_DIST_FROM_MOTOR0 * uS_PER_CM);
	}
	float encoderValPeruS = BOARD_SIZE / (BOARD_SIZE_CM * uS_PER_CM);
	return motorDistanceTime * encoderValPeruS - BOARD_SIZE/2;
}