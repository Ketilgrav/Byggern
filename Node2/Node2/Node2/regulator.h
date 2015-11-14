/*
 * regulator.h
 *
 * Created: 06.11.2015 11:02:21
 *  Author: sverrevr
 */ 


#ifndef REGULATOR_H_
#define REGULATOR_H_
#include "MotorDrivers/MotorBox.h"
#include "MainInclude.h"

#define CONTROLLER_GAIN 3

typedef struct PI{
	int8_t P;
	float I;
	int8_t D;
	int16_t u;
	
	float integralValue;
	//float refPosValue;
	int8_t prevVal;
} PI;

void regulator_init(PI* pi_state);
void regulator_increment(PI* pi_state, int16_t pos_ref, int16_t* joyPos, int16_t joySpeed);
int16_t get_pos_from_percent(int8_t percent);

#endif /* REGULATOR_H_ */