/*//
 * regulator.c
 *
 * Created: 06.11.2015 11:02:05
 *  Author: sverrevr
 */ 
#include "regulator.h"

void regulator_init(Regulator* regulator){
	regulator->P = 20;
	regulator->I = 10;
	regulator->D = 0.7;
	regulator->u= 0;
	regulator->integralValue = 0.0f;
	for(uint8_t i=0;i<DERIVATIVE_SAMPLES;++i){
		regulator->derivativeHistory[i] = 0;
	}
	regulator->derivativePointer = 0;
	//regulator->refPosValue = 0.0f;
	regulator->prevVal = 0;
	float dt = 0;
	/* Setter opp klokken som beregner tiden mellom hver incrementering*/
	//Bruker timer/counter 3 med normal opperation
}

void regulator_increment(Regulator* regulator, int16_t pos_ref){
	int16_t encoderPos = motorbox_get_encoder();
	int16_t avvik = (pos_ref-encoderPos)/(board_size/100); //I prosent, -100er motor helt til høyre, mens vi vil helt til venstre
	regulator->integralValue+=avvik*regulator->dt;
	float derivatLedd = 0;
	float sum = 0;
	if(regulator->dt != 0){
		regulator->derivativeHistory[regulator->derivativePointer] = (avvik-regulator->prevVal)/regulator->dt;
		regulator->derivativePointer ++;
		if(regulator->derivativePointer >= DERIVATIVE_SAMPLES){regulator->derivativePointer = 0; }
		for(uint8_t i = 0; i < DERIVATIVE_SAMPLES; ++i){
			sum += regulator->derivativeHistory[i];
		}
		derivatLedd = sum/DERIVATIVE_SAMPLES;
	}
	//printf("%f\r", derivatLedd);
	
	regulator->u =  avvik * regulator->P + regulator->integralValue * regulator->I + derivatLedd * regulator->D;
	regulator->prevVal = avvik;
}
int16_t get_pos_from_percent(int8_t percent){
	return (board_size/200) * percent;
}