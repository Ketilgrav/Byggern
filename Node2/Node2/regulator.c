/*//
 * regulator.c
 *
 * Created: 06.11.2015 11:02:05
 *  Author: sverrevr
 */ 
#include "regulator.h"

void regulator_init(Regulator* regulator){
	regulator->P = 40;
	regulator->I = 10;
	regulator->D = 0;
	regulator->u= 0;
	regulator->integralValue = 0.0f;
	//regulator->refPosValue = 0.0f;
	regulator->prevVal = 0;
	float dt = 0;
	/* Setter opp klokken som beregner tiden mellom hver incrementering*/
	//Bruker timer/counter 3 med normal opperation
	TCCR3B |= (0<<CS32)|(1<<CS31)|(1<<CS30); //aktiverer, med clock/1 prescaler. Kan da telle i 4ms, dette er for lite?
	//TIMSK3 = (1<<TOIE3); //Overflow interrupt enable
	//TCNT3 holder verdien, resettes ved å sette den lik 0;	
}

void regulator_increment(Regulator* regulator, int16_t pos_ref){
	int16_t encoderPos = motorbox_get_encoder();
	int16_t avvik = (pos_ref-encoderPos)/(board_size/100); //I prosent, -100er motor helt til høyre, mens vi vil helt til venstre
	regulator->integralValue+=avvik*regulator->dt;
	int16_t derivatLedd = 0;
	if(regulator->dt!= 0){
		derivatLedd = (avvik-regulator->prevVal)/regulator->dt;	
	}
	
	regulator->u =  avvik * regulator->P + regulator->integralValue * regulator->I + derivatLedd * regulator->D;
	regulator->prevVal = avvik;
}
int16_t get_pos_from_percent(int8_t percent){
	return (board_size/200) * percent;
}