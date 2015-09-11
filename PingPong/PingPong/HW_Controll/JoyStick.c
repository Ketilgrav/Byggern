/*
 * JoyStick.c
 *
 * Created: 11.09.2015 15:13:39
 *  Author: sverrevr
 */ 

#include "JoyStick.h"


void joystick_calibrate(JoyStick* js){
	js->x_rest = ADC_convert(channelX);
	js->y_rest = ADC_convert(channelY);
}

void joystick_update(JoyStick* js){
	js->x_voltage = ADC_convert(channelX);
	js->y_voltage = ADC_convert(channelY);
	js->x_percent = (js->x_voltage - js->x_rest)*100/js->x_rest;
	js->y_percent = (js->y_voltage - js->y_rest)*100/js->y_rest;
	
	joystick_descreet(&(js->x_descreet));
	joystick_descreet(&(js->y_descreet));
	
}

void joystick_descreet(int8_t* var){
	if(*var > slack){
		*var = 1;
	}
	else if(*var < -slack){
		*var = -1;
	}
	else{
		*var = 0;
	}
}