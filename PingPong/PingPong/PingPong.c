/*
 * PingPong.c
 *
 * Created: 28.08.2015 11:32:04
 *  Author: ketilgs
 */ 

//Bytt til den fancy screen moden, gir bonus.

#include "MainInclude/MainInclude.h"
#include "Drivers/UsartDriver.h"
#include "Drivers/external_SRAM.h"
#include "Drivers/ADC_Driver.h"
#include "Drivers/Controllers.h"
#include "Drivers/OLED.h"
#include "UI/Menu.h"

int main(void){
	USART_INIT();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	SRAM_INIT();
	ADC_init();
	OLED_init();
	set_bit(DDRB, PB0);
	
	
	
	controllers_init();
	JoyStick js;
	Slider s_l;
	Slider s_r;
	joystick_calibrate(&js);
	s_l.channel = 3;
	s_r.channel = 2;
	
	printf("\n\n\n");

		menyNode* menu = menu_init();
	menyNode* mainMenu = menu;
	
	unsigned short mainLoopCounter = 0;	
	
    while(1){
		//mainLoopCounter++;
		//if(!(mainLoopCounter%10)){
			toggle_bit(PORTB, PB0);
		//}
		joystick_update(& js);
		
		if(btn_B){ //Butt til en annen knapp som alltid returnerer til main
			menu = mainMenu;
			oled_clear_screen();
		}
		switch (menu->tilstand){
			case MENU:
				menu_go(&menu, &js);
				break;
			case RUN_GAME:
				//skal bare kjøre run game funksjon her
				oled_goto_line(3);
				oled_print("SPILLET KJORER");
				break;
			case HIGH_SCORE:
				//BARE HVIS HIGHSCORE FUNKSNONEN
				oled_goto_line(0);
				oled_print("Highscore");
				oled_goto_line(1);
				oled_print("  Per: 1024");
				
				if(js.x_descreet < 0 && js.x_descreet != js.x_prev_descreet){
					menu = mainMenu;
					oled_clear_screen();
				}
				
				break;
			case CALIBRATE_JS:
			
				oled_goto_line(0);
				oled_print("Calibrating JS");
				oled_clear_line(2);
				oled_print("Press A to");
				oled_clear_line(3);
				oled_print("calibrate");
				
				while(!btn_A)
				
				menu = mainMenu;
				oled_clear_screen();
				
				break;
			
		}
    }
}