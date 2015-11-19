/*
 * HC_SR04.c
 *
 * Created: 14.11.2015 14:23:44
 *  Author: sverrevr
 */ 

#include "HC-SR04.h"
volatile uint16_t sensor0Time = 0;
volatile uint16_t sensor1Time = 0;
volatile uint8_t doUpdate = 0;

volatile uint16_t nextSensor = SENSOR1;

//If the timer that counts the distance overflows
ISR(TIMER4_OVF_vect){
	printf("OVERFLOW");
	
	//Resets the inpterupt and time.
	ECHO_INTERRUPT_RISING(S0_ECHO_INTERRUPT_BIT);
	ECHO_INTERRUPT_RISING(S1_ECHO_INTERRUPT_BIT);
	ETIMER_MEASURE_DISABLE;
}

ISR(INT2_vect){
	handleInterrupt(SENSOR0, S0_ECHO_INTERRUPT_BIT);
}

ISR(INT3_vect){
	handleInterrupt(SENSOR1, S1_ECHO_INTERRUPT_BIT);
}


void handleInterrupt(uint8_t timerId, uint8_t edgeBit){
	//If we interrupted on rising
	if( ECHO_INTERRUPT_RISING_READ(edgeBit)){
		//if the timer is not turned off, meaning that another sensor is using it, then this interrupt is ignored
		if(ETIMER_MEASURE_ENABLE_READ){
			return;
		}
		ECHO_INTERRUPT_FALLING(edgeBit); //Change to interrupt on falling edge
		//Starts the timer:
		ETIMER_MEASURE_RESET;
		ETIMER_MEASURE_ENABLE;
	}
	//If we interrupted on falling
	else if(ECHO_INTERRUPT_FALLING_READ(edgeBit)){
		ECHO_INTERRUPT_RISING(edgeBit);
		//stops the timer and records the value.
		ETIMER_MEASURE_DISABLE;
		if(timerId == SENSOR0){
			sensor0Time = ETIMER_MEASURE;
		}
		else if(timerId == SENSOR1){
			sensor1Time = ETIMER_MEASURE;
		}
	}
	doUpdate = (1<<edgeBit);
}


ISR(ETIMER5_COMPA_vect){
	if(nextSensor == SENSOR1){
		nextSensor = SENSOR0;
		//Sends a 10us pulse on the trigger bit.
		set_bit(S1_TRIG_PORT,S1_TRIG_BIT);
		_delay_us(ECHO_TRIGGERPULSEWIDTH_us);
		clear_bit(S1_TRIG_PORT,S1_TRIG_BIT);
		ETIMER_TRIGGER_RESET;
	}
	else if(nextSensor == SENSOR0){
		nextSensor = SENSOR1;
		set_bit(S0_TRIG_PORT,S0_TRIG_BIT);
		_delay_us(ECHO_TRIGGERPULSEWIDTH_us);
		clear_bit(S0_TRIG_PORT,S0_TRIG_BIT);
		ETIMER_TRIGGER_RESET;
	}
	
}


void echo_init(){
	//porter
	set_bit(S0_TRIG_DDR,S0_TRIG_BIT);
	clear_bit(S0_ECHO_DDR,S0_ECHO_BIT);
	set_bit(S1_TRIG_DDR,S1_TRIG_BIT);
	clear_bit(S1_ECHO_DDR,S1_ECHO_BIT);
	
	//Echo intterupt
	ECHO_INTERRUPT_FALLING(S0_ECHO_INTERRUPT_BIT);
	set_bit(EIMSK,INT2);			//Enables interrupt
	ECHO_INTERRUPT_FALLING(S0_ECHO_INTERRUPT_BIT);
	set_bit(EIMSK,INT3);
	
	//Using timer 4 for both.
	set_bit(TIMSK4, 1<<TOIE4); //Activates overflow interrupt
	
	//Using timer 5 to send trigger signals for both sensors, alternating.
	//Set OC5A on compare match
	TCCR5A |= 0b11<<COM5A0;
	//Compare match on OC5A
	OCR5A = ECHO_MEASUREMENT_INTERVAL * F_CPU/ ECHO_PRESCALER;
	set_bit(TIMSK5, 1<<OCIE5A); //interrupt on compare match
}
void echo_data_init(ECHO_data* data){
	data->queuePointer = 0;
	data->pos_ref = 0;
	for(uint8_t i=0;i<ECHO_averagingPeriod;++i){
		data->mesurements[i] = 0;
	}
	data->sum = 0;
}



void echo_update_ref(ECHO_data* data, uint8_t sensorId, uint8_t edgeBit){
	if( !(doUpdate & (1<<edgeBit)) ) return;
	doUpdate &= (0<<edgeBit);
	
	uint16_t time;
	if(sensorId == SENSOR0){
		time = sensor0Time;
	}
	else if(sensorId == SENSOR1){
		time = sensor1Time;
	}
	
	int32_t encoderDist = echo_time_to_encoder_val(time);
	//Verdien er utenfor bordet, da ignoreres den
	if(encoderDist>BOARD_SIZE/2 || encoderDist<-BOARD_SIZE/2){
		return;
	}

	
	data->sum -= data->mesurements[data->queuePointer];
	data->sum += time;
	data->mesurements[data->queuePointer] = time;
	data->queuePointer++;
	if(data->queuePointer >= ECHO_averagingPeriod) data->queuePointer = 0;
	
	data->pos_ref = echo_time_to_encoder_val(data->sum/ECHO_averagingPeriod);
}

int32_t echo_time_to_encoder_val(uint16_t time){
	uint32_t distanceTime = (time * ECHO_PRESCALER)/16;	//Avstanden i uS fra sensoren
	uint32_t motorDistanceTime;								//Avstanden i uS fra startpossisjonen til motoren	
	if(distanceTime  <= ECHO_DIST_FROM_MOTOR0){
		motorDistanceTime = 0;								//Om denne er til venstre for boksen settes den til 0 for å unngå negative verdier, som uansett burde ignoreres siden motoren ikke kan dra hit.
	}
	else{
		motorDistanceTime = (distanceTime - ECHO_DIST_FROM_MOTOR0 * uS_PER_CM);
	}
	float encoderValPeruS = BOARD_SIZE*1.0 / (BOARD_SIZE_CM * uS_PER_CM);
	return (motorDistanceTime * encoderValPeruS - BOARD_SIZE/2);
}