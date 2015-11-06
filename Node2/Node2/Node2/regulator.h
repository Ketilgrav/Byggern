/*
 * regulator.h
 *
 * Created: 06.11.2015 11:02:21
 *  Author: sverrevr
 */ 


#ifndef REGULATOR_H_
#define REGULATOR_H_
#include "MotorDrivers/MotorBox.h"

typedef struct PI{
	uint8_t P;
	uint8_t I;
	
	uint8_t u;
	
	uint16_t integralValue;
	
	int16_t board_max;
} PI;

void regulator_init(PI* pi_state);
void regulator_increment(PI* pi_state, int8_t ref_percent);
int16_t get_pos_from_percent(PI* pi, int8_t percent);

#endif /* REGULATOR_H_ */