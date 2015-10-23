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
#define channel_R_slider 2
#define channel_L_slider 3
#define slack_js 50
#define slack_slider 15
#define slack_update_slider 11

#define btn_A read_bit(PINB,PB2)
#define btn_B read_bit(PINB,PB3)

typedef struct JoyStick{
	uint8_t x_voltage;
	uint8_t y_voltage;
	int8_t x_percent;
	int8_t y_percent;
	
	int8_t x_descreet;
	int8_t y_descreet;
	
	int8_t x_descreet_edge;
	int8_t y_descreet_edge;
	
	uint8_t x_rest;
	uint8_t y_rest;
} JoyStick;

typedef struct Slider{
	uint8_t l_voltage;
	int8_t l_percent;
	int8_t l_descreet;
	uint8_t r_voltage;
	int8_t r_percent;
	int8_t r_descreet;
} Slider;

typedef struct Buttons{
	uint8_t A;
	uint8_t B;
	uint8_t A_prev;
	uint8_t B_prev;
	uint8_t A_count;
	uint8_t B_count;
} Buttons;

typedef struct Controls{
	Buttons btns;
	Slider sliders;
	JoyStick js;
} Controls;

void joystick_calibrate(JoyStick* js);
uint8_t joystick_user_calibrate(JoyStick* js);
void joystick_update(JoyStick* js);
int8_t joystick_descreet(int8_t val);
void slider_update(Slider* sl);
void controllers_init();
void read_button(Buttons* btns);
void controllers_update(Controls* controls);
#endif /* JOYSTICK_H_ */