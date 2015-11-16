/*
 * PingPong.c
 *
 * Created: 28.08.2015 11:32:04
 *  Author: ketilgs
 */ 

//Bytt til den fancy screen moden, gir bonus.

#include "MainInclude.h"
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

#include <avr/eeprom.h>

int main(void){	
	//EEPROM test
	//eeprom_write_byte((uint8_t*) )
	
	/*Initialization*/
	USART_init();
	SRAM_init();
	ADC_init();
	OLED_init();
	CAN_init();
	controllers_init();
	
	set_bit(DDRB, PB0); //led init
	TCCR3B |= (1<<CS31); //Aktiverer timer med 1/8 prescaler, for 60Hz oppgaver.
	
	printf("\n\n\n");


	//Tillstandsvariabler
	Controls controls;
	joystick_calibrate(&controls.jsX,&controls.jsY);
	controls.btnR.edge = 0;
	controls.btnR.state = 0;
	
	menyNode* menu = menu_init();
	menyNode* mainMenu = menu;	
	
	interrupt CAN_interrupt = NOINT;
	
	unsigned short mainLoopCounter = 0;	
	
	GameState gameState;
	gameState.useJSnotSENS = 1;
	gameState.points = 0;
	
	//Testing variabler	
	interrupt test;
	
	CAN_message canMsgMotor;
	canMsgMotor.length = 0;
	canMsgMotor.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_MOTORSIGNALS;
	canMsgMotor.data[CANMSG_BTNR_BYTE] = 0;
	canMsgMotor.data[CANMSG_SLIDERR_BYTE] = 0;
	canMsgMotor.data[CANMSG_JSX_BYTE] = 0;
	canMsgMotor.id = NODE2_CANID_0;
	
	CAN_message canMsgGameMode;
	canMsgGameMode.length = 0;
	canMsgGameMode.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_GAMEMODE;
	canMsgGameMode.id = NODE2_CANID_HIGHPRIO_0;
	
	CAN_message canMsgInn;
	canMsgInn.length = 0;
	
	
    while(1){
		//Oppdater tilstandene ut ifra input
		controllers_update(&controls);
		CAN_interrupt = CAN_int();
		
		
		//Meny
		//Hver menytillstand kjører en funksjon, returverdien fra funksjonen er om vi skal returnere til mainMenu. 
		//Returner tilbake til hovedmenyen
		if(controls.btnL.edge){
			menu = mainMenu;
		}
		switch (menu->tilstand){
			case MENU:
				//printf("MENU");
				menu_go(&menu, &controls);
				if(canMsgGameMode.data[GAMEMODE_MODE_BYTE] != GAMEMODE_OFF){
					canMsgGameMode.length = GAMEMODE_MSGLEN;
					canMsgGameMode.data[GAMEMODE_MODE_BYTE] = GAMEMODE_OFF;	
				}
				break;
			case RUN_GAME:
				if(gameState.useJSnotSENS == 1 && canMsgGameMode.data[GAMEMODE_MODE_BYTE] != GAMEMODE_JS){
					canMsgGameMode.length = GAMEMODE_MSGLEN;
					canMsgGameMode.data[GAMEMODE_MODE_BYTE] = GAMEMODE_JS;
				}
				else if(gameState.useJSnotSENS == 0 && canMsgGameMode.data[GAMEMODE_MODE_BYTE] != GAMEMODE_SENS){
					canMsgGameMode.length = GAMEMODE_MSGLEN;
					canMsgGameMode.data[GAMEMODE_MODE_BYTE] = GAMEMODE_SENS;
				}
				if(runGame(&gameState,&controls,&canMsgMotor,&canMsgInn)){
					menu = mainMenu;
				}
				break;
			case HIGH_SCORE:
				//printf("HS");
				if(displayHighScore(&controls)){
					menu = mainMenu;
				}
				break;
			case CALIBRATE_JS:
				//printf("Calibrate");
				if(joystick_user_calibrate(&controls)){
					menu = mainMenu;
				}
				break;
			case SHOW_CAN_MSG:
				oled_clear();
				oled_print("Unused", 0, 0);
				break;
			case CNTRL_JS:
				//printf("ho\n");
				gameState.useJSnotSENS = 1;
				menu = mainMenu;
				break;
			case CNTRL_SENS:		
				//printf("ho\n");
				gameState.useJSnotSENS = 0;
				menu = mainMenu;
				break;
		}
		
		
		//Interupt håndtering
		switch(CAN_interrupt){
			case NOINT:
				break;
			case ERR:
				printf("CAN error");
				break;
			case RX0:
				CAN_data_receive(&canMsgInn, MCP_RXB0CTRL);
				break;
			case RX1:
				CAN_data_receive(&canMsgInn, MCP_RXB1CTRL);
				break;
			default:

				break;
		}
		CAN_int_clear(CAN_interrupt);	
		
		
		//60hz tasks
		if(TCNT3 > (F_CPU/(8*60))){
			mainLoopCounter++;
			if(!(mainLoopCounter%60)){
				toggle_bit(PORTB, PB0);
			}
			if(canMsgGameMode.length){
				CAN_message_send(&canMsgGameMode);
				canMsgGameMode.length = 0;
			}
			if(canMsgMotor.length){
				CAN_message_send(&canMsgMotor);
				canMsgMotor.length = 0;
			}
			
			oled_update_screen();
			TCNT3 = 0;	//Reset timer
			printf("%i \r",gameState.useJSnotSENS);
		}
    }
}