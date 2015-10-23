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
}


void joystick_calibrate(JoyStick* js){
	js->x_rest = ADC_convert(channelX);
	js->y_rest = ADC_convert(channelY);
}

uint8_t joystick_user_calibrate(JoyStick* js){
	oled_mem_clear();
	oled_mem_print("Calibrating JS: ",0,0);
	oled_mem_print("Press A to      ",2,0);
	oled_mem_print("calibrate       ",3,0);
	
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
	
	int8_t xDescTemp = joystick_descreet(js->x_percent);
	int8_t yDescTemp = joystick_descreet(js->y_percent);
	
	if(xDescTemp != js->x_descreet){
		js->x_descreet_edge = xDescTemp;
	}
	else{
		js->x_descreet_edge = 0;
	}
	
	if(yDescTemp != js->y_descreet){
		js->y_descreet_edge = yDescTemp;
	}
	else{
		js->y_descreet_edge = 0;
	}
	
	js->x_descreet = xDescTemp;
	js->y_descreet = yDescTemp;
	
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
	uint8_t r_voltage = ADC_convert(channel_R_slider);
	uint8_t l_voltage = ADC_convert(channel_L_slider);
	
	if(l_voltage < sl->l_voltage - slack_update_slider  || l_voltage > sl->l_voltage + slack_update_slider){
		sl->l_voltage = l_voltage;
		sl->l_percent = (2*sl->l_voltage/2.55) - 100;
		if(sl->l_percent < 50-slack_slider){
			sl->l_descreet = -1;
		}
		else if(sl->l_percent > 50 + slack_slider){
			sl->l_descreet = + 1;
		}
		else{
			sl->l_descreet = 0;
		};
	}
	if(r_voltage < sl->r_voltage - slack_update_slider  || r_voltage > sl->r_voltage + slack_update_slider){
		sl->r_voltage = r_voltage;
		sl->r_percent = (2*sl->r_voltage/2.55) - 100;
		if(sl->r_percent < 50 - slack_slider){
			sl->r_descreet =	-1;
		}
		else if(sl->r_percent > 50 + slack_slider){
			sl->r_descreet = + 1;
		}
		else{
			sl->r_descreet = 0;
		};
	}

	
}

void read_button(Buttons* btns){
	btns->A = 0;
	btns->B = 0;
	if (btn_A != btns->A_prev && btns->A_prev == 0){
		btns->A = 1;
		btns->A_count++;
	}
	if (btn_B != btns->B_prev && btns->B_prev == 0){
		btns->B = 1;
		btns->B_count++;
	}
	btns->A_prev = btn_A;
	btns->B_prev = btn_B;
	
}

void controllers_update(Controls* controls){
		joystick_update(&controls->js);
		slider_update(&controls->sliders);
		read_button(&controls->btns);
}