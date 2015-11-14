/*//
 * regulator.c
 *
 * Created: 06.11.2015 11:02:05
 *  Author: sverrevr
 */ 
#include "regulator.h"

void regulator_init(PI* pi_state){
	pi_state->P = 2;
	pi_state->I = 1;
	pi_state->D	= 1;
	pi_state->u= 0;
	pi_state->integralValue = 0.0f;
	//pi_state->refPosValue = 0.0f;
	pi_state->prevVal = 0;
	/* Setter opp klokken som beregner tiden mellom hver incrementering*/
	//Bruker timer/counter 3 med normal opperation
	TCCR3B |= (0<<CS32)|(1<<CS31)|(1<<CS30); //aktiverer, med clock/1 prescaler. Kan da telle i 4ms, dette er for lite?
	//TIMSK3 = (1<<TOIE3); //Overflow interrupt enable
	//TCNT3 holder verdien, resettes ved å sette den lik 0;	
}

void regulator_increment(PI* piState, int16_t sensPos, int16_t* joyPos, int16_t joySpeed){
	float dt = TCNT3*1.0/((F_CPU/64)*1.0);
	TCNT3 = 0;
	
	*joyPos += get_pos_from_percent(joySpeed)*dt *CONTROLLER_GAIN;
	
	int16_t ref = *joyPos; //bytt med sensPos for sensor.
	
	int16_t encoderPos = motorbox_get_encoder();
	int16_t avvik = (ref-encoderPos)/(board_size/100); //I prosent, -100er motor helt til høyre, mens vi vil helt til venstre
	piState->integralValue+=avvik*dt;
	int16_t derivatLedd = (avvik-piState->prevVal)/dt;
	
	//printf("PosRef: %f     \tEncodePos: %i      \tAvvik: %i     \tIntegralVal: %f    \r", piState->refPosValue, encoderPos, avvik, piState->integralValue);
	piState->u =  avvik * piState->P + piState->integralValue * piState->I + derivatLedd * piState->D;
	
	piState->prevVal = avvik;
}
int16_t get_pos_from_percent(int8_t percent){
	return (board_size/200) * percent;
}