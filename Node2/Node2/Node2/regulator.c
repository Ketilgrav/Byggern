/*//
 * regulator.c
 *
 * Created: 06.11.2015 11:02:05
 *  Author: sverrevr
 */ 
#include "regulator.h"

void regulator_init(PI* pi_state){
	pi_state->P = 2;
	pi_state->I = 20;
	pi_state->u= 0;
	pi_state->integralValue = 0.0f;
	pi_state->refPosValue = 0.0f;
	/* Setter opp klokken som beregner tiden mellom hver incrementering*/
	//Bruker timer/counter 3 med normal opperation
	TCCR3B |= (0<<CS32)|(1<<CS31)|(1<<CS30); //aktiverer, med clock/1 prescaler. Kan da telle i 4ms, dette er for lite?
	TIMSK3 = (1<<TOIE3); //Overflow interrupt enable
	//TCNT3 holder verdien, resettes ved å sette den lik 0;	
}

void regulator_increment(PI* piState, int8_t refSpeedPercent){
	float dt = TCNT3*1.0/((F_CPU/64)*1.0);
	TCNT3 = 0;
	piState->refPosValue += get_pos_from_percent(refSpeedPercent)*dt *CONTROLLER_GAIN;
	int16_t encoderPos = motorbox_get_encoder();
	int16_t avvik = (piState->refPosValue-encoderPos)/(board_size/100); //I prosent, -100er motor helt til høyre, mens vi vil helt til venstre
	piState->integralValue+=avvik*dt;
	
	printf("Pos: %e     \r", piState->refPosValue );
	piState->u =  avvik * piState->P + piState->integralValue * piState->I;
}
int16_t get_pos_from_percent(int8_t percent){
	return (board_size/200) * percent;
}