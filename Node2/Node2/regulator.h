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

#define CONTROLLER_GAIN 2
#define DERIVATIVE_SAMPLES 10
typedef struct Regulator{
	float P;
	float I;
	float D;
	int16_t u;
	float integralValue;
	float derivativeHistory[DERIVATIVE_SAMPLES];
	uint8_t derivativePointer;
	int8_t prevVal;
	float dt;
} Regulator;

#define REGULATOR_TIMER 
#define REGULATOR_TIMER_PRESCALER TCCR3B
#define REGULATOR_TIMER_PRESCALER_VAL (0<<CS32)|(1<<CS31)|(1<<CS30)
#define REGULATOR_TIMER_ACTIVATE (REGULATOR_TIMER_PRESCALER |= REGULATOR_TIMER_PRESCALER_VAL)
#define REGULATOR_TIMER_DEACTIVATE (REGULATOR_TIMER_PRESCALER &= ~(0b111))


void regulator_init(Regulator* pi_state);
void regulator_increment(Regulator* pi_state, int16_t pos_ref);
int16_t get_pos_from_percent(int8_t percent);

#endif /* REGULATOR_H_ */