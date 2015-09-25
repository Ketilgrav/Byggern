/*
 * JoyStick.c
 *
 * Created: 11.09.2015 15:13:39
 *  Author: sverrevr
 */ 

#include "Controllers.h"

void controllers_init(){
		clear_bit(DDRB, PB2);
		clear_bit(DDRB, PB3);
		clear_bit(DDRB, PB4);
}


void joystick_calibrate(JoyStick* js){
	js->x_rest = ADC_convert(channelX);
	js->y_rest = ADC_convert(channelY);
}

uint8_t joystick_user_calibrate(JoyStick* js){
	oled_goto_line(0);
	oled_print("Calibrating JS: ");
	oled_goto_line(2);
	oled_print("Press A to      ");
	oled_goto_line(3);
	oled_print("calibrate       ");
	
	if(btn_A){
		joystick_calibrate(js);
		return 1;
	}
	return 0;
	
}

void joystick_update(JoyStick* js){
	js->x_voltage = ADC_convert(channelX);
	js->y_voltage = ADC_convert(channelY);
	if(js->x_voltage <= js->x_rest){
		js->x_percent = (js->x_voltage - js->x_rest)*100/(js->x_rest-1);
	}
	else{
		js->x_percent = (js->x_voltage - js->x_rest)*100/(255-js->x_rest);
	}
	if(js->y_voltage <= js->y_rest){
		js->y_percent = (js->y_voltage - js->y_rest)*100/(js->y_rest-1);
	}
	else{
		js->y_percent = (js->y_voltage - js->y_rest)*100/(255-js->y_rest);
	}
	
	js->x_prev_descreet = js->x_descreet;
	js->y_prev_descreet = js->y_descreet;
	
	js->x_descreet = joystick_descreet(js->x_percent);
	js->y_descreet = joystick_descreet(js->y_percent);
	
}

int8_t joystick_descreet(int8_t val){
	if(val > slack_js){
		return 1;
	}
	else if(val < -slack_js){
		return -1;
	}
	else{
		return 0;
	}
}


void slider_update(Slider* sl){
	sl->voltage = ADC_convert(sl->channel);
	sl->percent = sl->voltage/2.55;
	if(sl->percent < 50-slack_slider){
		sl->descreet =	-1;
	}
	else if(sl->percent > 50+slack_slider){
		sl->descreet =	+1;
	}
	else{
		sl->descreet =	0;
	}
}