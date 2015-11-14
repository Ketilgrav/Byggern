/*
 * JoyStick.h
 *
 * Created: 11.09.2015 15:17:59
 *  Author: sverrevr
 */ 


#ifndef CONTROLLERS_H_
#define CONTROLLERS_H_

#include "../MainInclude.h"
#include "../Drivers/ADC_Driver.h"

#define channelX 1
#define channelY 0
#define channel_R_slider 3
#define channel_L_slider 2
#define slack_js 50
#define slack_slider 15
#define slack_update_slider 11

#define btn_A read_bit(PINB,PB2)
#define btn_B read_bit(PINB,PB3)

typedef struct JoyStick{
	uint8_t voltage;
	int8_t percent;
	int8_t descreet;
	int8_t descreet_edge;	
	uint8_t rest;
} JoyStick;

typedef struct Slider{
	uint8_t voltage;
	int8_t percent;
	int8_t descreet;
} Slider;

typedef struct Button{
	uint8_t state;
	uint8_t edge;
	uint8_t pressCount;
} Button;

typedef struct Controls{
	Button btnL;
	Button btnR;
	Slider sliderL;
	Slider sliderR;
	JoyStick jsX;
	JoyStick jsY;
} Controls;

void joystick_calibrate(JoyStick* jsX, JoyStick* jsY);
uint8_t joystick_user_calibrate(Controls* control);
void joystick_update(JoyStick* jsX, JoyStick* jsY);
int8_t joystick_descreet(int8_t val);
void slider_update(Slider* slL, Slider* slR);
void controllers_init();
void read_button(Button* btnL, Button* btnR);
void controllers_update(Controls* controls);
#endif /* JOYSTICK_H_ */