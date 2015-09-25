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
#include "Game/Game.h"
#include "UI/HighScore.h"

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
		//Main loop counter and blinker
		mainLoopCounter++;
		if(!(mainLoopCounter%10)){
			toggle_bit(PORTB, PB0);
		}
		
		//Oppdater tillstandene ut ifra input
		joystick_update(&js);
		slider_update(&s_l);
		slider_update(&s_r);
		
		
		//Meny og program kjøring:
		
		//Ved trykk av start går man uansett til main menu.
		if(btn_B){ //Butt til en annen knapp som alltid returnerer til main
			menu = mainMenu;
			oled_clear_screen();
		}
		switch (menu->tilstand){
			case MENU:
				menu_go(&menu, &js);
				break;
			case RUN_GAME:
				if(runGame(&js,&s_l,&s_r)){
					menu = mainMenu;
					oled_clear_screen();
				}
				break;
			case HIGH_SCORE:
				if(displayHighScore(&js)){
					menu = mainMenu;
					oled_clear_screen();
				}
				break;
			case CALIBRATE_JS:
				if(joystick_user_calibrate(&js)){
					menu = mainMenu;
					oled_clear_screen();
				}
				break;
			/*case TILSTAND:
				if(funksjonen til tillstanden som returnerer true om vi skal tilbake til menyen){
					menu = mainMenu;
					oled_clear_screen();
				}*/
		}
		
		
    }
}