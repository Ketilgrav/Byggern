/*
 * JoyStick.h
 *
 * Created: 11.09.2015 15:17:59
 *  Author: sverrevr
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "../MainInclude/MainInclude.h"
#include "../Drivers/ADC_Driver.h"

#define channelX 1
#define channelY 0
#define slack 15

typedef struct JoyStick{
	uint8_t x_voltage;
	uint8_t y_voltage;
	int8_t x_percent;
	int8_t y_percent;
	int8_t x_descreet;
	int8_t y_descreet;
	
	uint8_t x_rest;
	uint8_t y_rest;
} JoyStick;


void joystick_calibrate(JoyStick* js);
void joystick_update(JoyStick* js);
void joystick_descreet(int8_t* var);

#endif /* JOYSTICK_H_ */