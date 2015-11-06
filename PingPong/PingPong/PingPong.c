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
#include "Communication_drivers/can.h"

#include <stdio.h>

int main(void){	
	
	USART_init();
	SRAM_init();
	ADC_init();
	OLED_init();
	CAN_init();
	controllers_init();
	set_bit(DDRB, PB0); //led, blink
	
	Controls controls;
	joystick_calibrate(&controls.js);

	
	printf("\n\n\n");

	//Tillstandsvariabler
	menyNode* menu = menu_init();
	menyNode* mainMenu = menu;	
	interrupt CAN_interrupt = NOINT;
	
	unsigned short mainLoopCounter = 0;
	
	//Testing variabler	
	interrupt test;

	CAN_message msgInn0;
	CAN_message msgInn1;
	
	CAN_message msgOut0;
	msgOut0.data[0] = 'a';
	msgOut0.data[1] = '\0';
	msgOut0.length = 2;
	msgOut0.id = 0b00100000001;
	msgOut0.priority = 1;

    while(1){
		//Main loop counter and blinker
		mainLoopCounter++;
		if(!(mainLoopCounter%100)){
			toggle_bit(PORTB, PB0);
		}
		
		//Oppdater tilstandene ut ifra input
		controllers_update(&controls);
		CAN_interrupt = CAN_int();
		
		
		//Meny og program kjøring
		//Ved trykk av start går man uansett til main menu.
		if(controls.btns.B){ //Bytt til en annen knapp som alltid returnerer til main
			menu = mainMenu;
		}
		switch (menu->tilstand){
			case MENU:
				printf("MENU");
				menu_go(&menu, &controls.js);
				break;
			case RUN_GAME:
				printf("RUN_GAME");
				if(runGame(&controls)){
					menu = mainMenu;
				}
				break;
			case HIGH_SCORE:
				printf("HS");
				if(displayHighScore(&controls.js)){
					menu = mainMenu;
				}
				break;
			case CALIBRATE_JS:
				printf("Calibrate");
				if(joystick_user_calibrate(&controls.js)){
					menu = mainMenu;
				}
				break;
			case SHOW_CAN_MSG:
				printf("Show msg");
				oled_mem_clear();
				oled_mem_print(menu->tekst,0,0);
				oled_mem_print("MSG0:",2,0);
				oled_mem_print(msgInn0.data,3,0);
				oled_mem_print("MSG1:",5,0);
				oled_mem_print(msgInn1.data,6,0);
				break;
				
		}
		
		//Interupts
		switch(CAN_interrupt){
			case NOINT:
				break;
			case ERR:
				//printf("roFL eRRoR LOLz\n\r");
				break;
			case RX0:
				//printf("RECEIVED ON RX0\n\r");
				CAN_data_receive(&msgInn0, MCP_RXB0CTRL);
				break;
			case RX1:
				//printf("RECEIVED ON RX1\n\r");
				CAN_data_receive(&msgInn1, MCP_RXB1CTRL);
				break;
			default:

				break;
		}
		CAN_int_clear(CAN_interrupt);
		oled_mem_update_screen();
    }
}