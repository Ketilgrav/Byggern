/*
 * JoyStick.c
 *
 * Created: 11.09.2015 15:13:39
 *  Author: sverrevr
 */ 

#include "Controllers.h"

void controllers_init(){
	clear_bit(BTN_R_DDR, BTN_R_BIT);
	clear_bit(BTN_L_DDR, BTN_L_BIT);
}


void joystick_calibrate(JoyStick* jsX, JoyStick* jsY){
	jsX->rest = ADC_convert(CHANNEL_X);
	jsY->rest = ADC_convert(CHANNEL_Y);
}

uint8_t joystick_user_calibrate(Controls* control){
	OLED_clear();
	OLED_print("Calibrating JS: ",0,0);
	OLED_print("Press R to      ",2,0);
	OLED_print("calibrate       ",3,0);
	
	if(control->btnR.edge){
		joystick_calibrate(&control->jsX,&control->jsY);		
		return 1;
	}
	return 0;
	
}

void joystick_update(JoyStick* jsX, JoyStick* jsY){
	jsX->voltage = ADC_convert(CHANNEL_X);
	jsY->voltage = ADC_convert(CHANNEL_Y);
	
	if(jsX->voltage <= jsX->rest){
		jsX->percent = (jsX->voltage - jsX->rest)*100/(jsX->rest-1);
	}
	else{
		jsX->percent = (jsX->voltage - jsX->rest)*100/(255-jsX->rest);
	}
	if(jsY->voltage <= jsY->rest){
		jsY->percent = (jsY->voltage - jsY->rest)*100/(jsY->rest-1);
	}
	else{
		jsY->percent = (jsY->voltage - jsY->rest)*100/(255-jsY->rest);
	}
	
	int8_t xDescTemp = joystick_descreet(jsX->percent);
	int8_t yDescTemp = joystick_descreet(jsY->percent);
	
	if(xDescTemp != jsX->descreet){
		jsX->descreet_edge = xDescTemp;
	}
	else{
		jsX->descreet_edge = 0;
	}
	
	if(yDescTemp != jsY->descreet){
		jsY->descreet_edge = yDescTemp;
	}
	else{
		jsY->descreet_edge = 0;
	}
	
	jsX->descreet = xDescTemp;
	jsY->descreet = yDescTemp;
	
}

int8_t joystick_descreet(int8_t val){
	if(val > SLACK_JS){
		return 1;
	}
	else if(val < -SLACK_JS){
		return -1;
	}
	else{
		return 0;
	}
}


void slider_update(Slider* slL, Slider* slR){
	uint8_t r_voltage = ADC_convert(CHANNEL_R_SLIDER);
	uint8_t l_voltage = ADC_convert(CHANNEL_L_SLIDER);
	
	if(l_voltage < slL->voltage - SLACK_UPDATE_SLIDER  || l_voltage > slL->voltage + SLACK_UPDATE_SLIDER){
		slL->voltage = l_voltage;
		slL->percent = (2*slL->voltage/2.55) - 100;
		if(slL->percent < 50-SLACK_SLIDER){
			slL->descreet = -1;
		}
		else if(slL->percent > 50 + SLACK_SLIDER){
			slL->descreet = + 1;
		}
		else{
			slL->descreet = 0;
		};
	}
	if(r_voltage < slR->voltage - SLACK_UPDATE_SLIDER  || r_voltage > slR->voltage + SLACK_UPDATE_SLIDER){
		slR->voltage = r_voltage;
		slR->percent = (2*slR->voltage/2.55) - 100;
		if(slR->percent < 50 - SLACK_SLIDER){
			slR->descreet =	-1;
		}
		else if(slR->percent > 50 + SLACK_SLIDER){
			slR->descreet = + 1;
		}
		else{
			slR->descreet = 0;
		};
	}
}

void read_button(Button* btnL, Button* btnR){	
	btnL->edge = 0;
	btnR->edge = 0;
	
	if (BTN_R != btnL->state && btnL->state == 0){
		btnL->edge = 1;
		btnL->pressCount++;
	}
	if (BTN_L != btnR->state && btnR->state == 0){
		btnR->edge = 1;
		btnR->pressCount++;
	}
	
	btnL->state = BTN_R;
	btnR->state = BTN_L;
}

void controllers_update(Controls* controls){
		joystick_update(&controls->jsX, &controls->jsY);
		slider_update(&controls->sliderL, &controls->sliderR);
		read_button(&controls->btnL, &controls->btnR);
}
