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

void HCSR04_inti(){
	
	//porter
	set_bit(S0_TRIG_DDR,S0_TRIG_BIT);
	clear_bit(S0_ECHO_DDR,S0_ECHO_BIT);
	set_bit(S1_TRIG_DDR,S1_TRIG_BIT);
	clear_bit(S1_ECHO_DDR,S1_ECHO_BIT);
	
	//Echo intterupt
	EICRA |= (1<<ISC21)|(1<<ISC20); //Set ISC20 to 0 to interrupt on falling edge
	set_bit(EIMSK,INT2);	//Enables interrupt
	EICRA |= (1<<ISC31)|(1<<ISC30);
	set_bit(EIMSK,INT3);
	
	//Using timer 4 for both.
	//TCCR4B |= 0b011<<CS40; //aktiver med 1/64 prescaler
	//TCNT4 verdien
	TIMSK4 |= 1<<TOIE4;
	
	//Using timer 5 to send trigger signals for both sensors, alternating.
	//Activates every 60ms
	//Set OC5A on compare match
	TCCR5A |= 0b11<<COM5A0;
	//Clocksclaer på 1/64, dette gjør 60ms til 15000
	TCCR5B |= 0b011<<CS50;
	OCR5A = HCSR04_MEASUREMENT_INTERVAL * F_CPU/ HCSR04_PRESCALER;
	TIMSK5 |= 1<<OCIE5A; //interrupt on compare match
}

ISR(TIMER4_OVF_vect){
	printf("OVERFLOW");
	set_bit(EICRA,ISC20); //Change to interrupt on rising edge
	TCCR4B &= ~(0b111 << CS40); //Turnes of the timer
}

ISR(INT2_vect){
	handleInterrupt(SENSOR0, ISC20);	
}

ISR(INT3_vect){
	handleInterrupt(SENSOR1, ISC30);	
}

ISR(BADISR_vect, ISR_NAKED)
{
	puts("Bad interrupt");
	asm volatile ( "ret" ); //Er dette rett, anders skrev iret
	//while(1){}
}


// LA TIL EDGEBIT HER!!! DEN RESETTA KUN INTERRUPT PIN 2 IKKE 3!!! edgeBit erstattet ISC20
// LA OGSÅ DENNE FUNKSJONEN INN I H FILA! DEN VAR IKKE DEKLARERT!=?!?!??!?!?!
void handleInterrupt(uint8_t timerId, uint8_t edgeBit){
	//If we interrupted on rising
	if( EICRA & (1<<edgeBit)){
		//if the timer is not turned off, meaning that another sensor is using it, then this interrupt is ignored
		if(TCCR4B & (0b111<<CS40)){
			return;
		}
		clear_bit(EICRA, edgeBit); //Change to interrupt on falling edge
		//Starts the timer:
		TCNT4 = 0;
		TCCR4B |= 0b010 << CS40; // 1/8 pre scaler
	}
	//If we interrupted on falling
	else if(!(EICRA & (1<<edgeBit))){
		set_bit(EICRA, edgeBit); //Change to interrupt on rising edge
		//stops the timer and records the value.
		TCCR4B &= ~(0b111 << CS40);
		//Ignoring the timer value if an overflow occurred
		if(!read_bit(TIFR4, TOV4)){
			if(timerId == SENSOR0){
				sensor0Time = TCNT4;
			}
			else if(timerId == SENSOR1){
				sensor1Time = TCNT4;
			}
		}
		else{
			set_bit(TIFR4, TOV4); //Resets the flag
		}		
	}
	doUpdate = (1<<edgeBit);
}


ISR(TIMER5_COMPA_vect){
	//puts("a");
	if(nextSensor == SENSOR1){
		nextSensor = SENSOR0;
		//Sends a 10us pulse on the trigger bit.
		set_bit(S1_TRIG_PORT,S1_TRIG_BIT);
		_delay_us(HCSR04_TRIGGERPULSEWIDTH_us);
		clear_bit(S1_TRIG_PORT,S1_TRIG_BIT);
		TCNT5 = 0;
	}
	else if(nextSensor == SENSOR0){
		//printf("Bola");
		nextSensor = SENSOR1;
		set_bit(S0_TRIG_PORT,S0_TRIG_BIT);
		_delay_us(HCSR04_TRIGGERPULSEWIDTH_us);
		clear_bit(S0_TRIG_PORT,S0_TRIG_BIT);
		TCNT5 = 0;
	}
	
}


// LA TIL EDGEBIT HER!!! DEN UPDATA KUN DEN FØRSTE
void HCSR04_update_ref(HCSR04_data* data, uint8_t sensorId, uint8_t edgeBit){
	if( !(doUpdate & (1<<edgeBit)) ) return;
	doUpdate &= (0<<edgeBit);
	
	uint16_t time;
	if(sensorId == SENSOR0){
		time = sensor0Time;
		//puts("S1");
	}
	else if(sensorId == SENSOR1){
		time = sensor1Time;
		//puts("S2");
	}
	
	int32_t encoderDist = echo_time_to_encoder_val(time);
	//Verdien er utenfor bordet, da ignoreres den
	if(encoderDist>BOARD_SIZE/2 || encoderDist<-BOARD_SIZE/2){
		//puts("too far\r\n");
		return;
	}

	
	data->sum -= data->mesurements[data->queuePointer];
	data->sum += time;
	data->mesurements[data->queuePointer] = time;
	data->queuePointer++;
	if(data->queuePointer >= HCSR04_averagingPeriod) data->queuePointer = 0;
	
	data->pos_ref = echo_time_to_encoder_val(data->sum/HCSR04_averagingPeriod);
}

int32_t echo_time_to_encoder_val(uint16_t time){
	uint32_t distanceTime = (time * HCSR04_PRESCALER)/16;	//Avstanden i uS fra sensoren
	uint32_t motorDistanceTime;								//Avstanden i uS fra startpossisjonen til motoren	
	if(distanceTime  <= HCSR04_DIST_FROM_MOTOR0){
		motorDistanceTime = 0;								//Om denne er til venstre for boksen settes den til 0 for å unngå negative verdier, som uansett burde ignoreres siden motoren ikke kan dra hit.
	}
	else{
		motorDistanceTime = (distanceTime - HCSR04_DIST_FROM_MOTOR0 * uS_PER_CM);
	}
	float encoderValPeruS = BOARD_SIZE*1.0 / (BOARD_SIZE_CM * uS_PER_CM);
	return (motorDistanceTime * encoderValPeruS - BOARD_SIZE/2);
}