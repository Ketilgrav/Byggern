/*
 * regulator.c
 *
 * Created: 06.11.2015 11:02:05
 *  Author: sverrevr
 */ 
#include "regulator.h"

void regulator_init(PI* pi_state){
	pi_state->P = 1;
	pi_state->I = 1;
	pi_state->u= 0;
	pi_state->integralValue = 0;
	pi_state->board_max = 8800;
	
	/* Setter opp klokken som beregner tiden mellom hver incrementering*/
	//Bruker timer/counter 3 med normal opperation
	TCCR3B |= (1<<CS10); //aktiverer, med clock/1 prescaler. Kan da telle i 4ms, dette er for lite?
	//TCNT3 holder verdien, resettes ved å sette den lik 0;	
}

void regulator_increment(PI* pi_state, int8_t ref_percent){
	int16_t possition = motorbox_get_encoder();
	int16_t ref = get_pos_from_percent(pi_state,ref_percent);
	uint16_t avvik = ref - possition;
	uint8_t dt;
	u = P*avvik + I*(integralValue+=avvik*dt);
}
int16_t get_pos_from_percent(PI* pi, int8_t percent){
	int16_t midPoint = (pi->board_max)/2;
	return((pi->board_max - midPoint) * percent / 100) + midPoint;
}