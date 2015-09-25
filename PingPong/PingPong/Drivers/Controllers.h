/*
 * JoyStick.h
 *
 * Created: 11.09.2015 15:17:59
 *  Author: sverrevr
 */ 


#ifndef CONTROLLERS_H_
#define CONTROLLERS_H_

#include "../MainInclude/MainInclude.h"
#include "../Drivers/ADC_Driver.h"

#define channelX 1
#define channelY 0
#define slack_js 50
#define slack_slider 15

#define btn_A read_bit(PINB,PB2)
#define btn_B read_bit(PINB,PB3)

typedef struct JoyStick{
	uint8_t x_voltage;
	uint8_t y_voltage;
	int8_t x_percent;
	int8_t y_percent;
	
	int8_t x_prev_descreet;
	int8_t y_prev_descreet;
	int8_t x_descreet;
	int8_t y_descreet;
	
	uint8_t x_rest;
	uint8_t y_rest;
} JoyStick;


typedef struct Slider{
	uint8_t channel;
	uint8_t voltage;
	int8_t percent;
	int8_t descreet;
} Slider;

void joystick_calibrate(JoyStick* js);
uint8_t joystick_user_calibrate(JoyStick* js);
void joystick_update(JoyStick* js);
int8_t joystick_descreet(int8_t val);
void slider_update(Slider* sl);
void controllers_init();
#endif /* JOYSTICK_H_ */