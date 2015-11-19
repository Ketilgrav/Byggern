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

#define CHANNEL_X 1
#define CHANNEL_Y 0
#define CHANNEL_R_SLIDER 3
#define CHANNEL_L_SLIDER 2
#define SLACK_JS 50
#define SLACK_SLIDER 15
#define SLACK_UPDATE_SLIDER 11

#define BTN_R_DDR DDRB
#define BTN_R_BIT PB2
#define BTN_L_DDR DDRB
#define BTN_L_BIT PB3

#define BTN_R read_bit(PINB, BTN_R_BIT)
#define BTN_L read_bit(PINB, BTN_L_BIT)

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
