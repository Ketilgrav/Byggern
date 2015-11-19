/*
 * PingPong.c
 *
 * Created: 28.08.2015 11:32:04
 *  Author: ketilgs
 */ 

//Bytt til den fancy screen moden, gir bonus.

#include "MainInclude.h"
#include "CommunicationDrivers/UsartDriver.h"
#include "Drivers/external_SRAM.h"
#include "Drivers/ADC_Driver.h"
#include "Drivers/Controllers.h"
#include "Drivers/OLED.h"
#include "UI/Menu.h"
#include "Game/Game.h"
#include "UI/HighScore.h"
#include "CommunicationDrivers/can.h"
#include "Game/EEPROM.h"
#include "main.h"

int main(void){	
	//x_delay_ms(10);
	set_bit(LED_DDR, LED_BIT);
	/*Initialization*/
	USART_init();
	//puts("USART init done");
	
	SRAM_init();
	//puts("SRAM init done");
	ADC_init();
	//puts("ADC init done");
	set_bit(PORTB, 0);
	OLED_init();
	//puts("OLED init done");
	CAN_init();
	//puts("CAN inti done");
	controllers_init();
	//puts("Controller init done");
	
	set_bit(LED_DDR, LED_BIT);
	TIMER_60HZ_ACTIVATE;
	//puts("Timer init done");

	//Tillstandsvariabler
	Controls controls;
	joystick_calibrate(&controls.jsX,&controls.jsY);
	controls.btnR.edge = 0;
	controls.btnR.state = 0;
	
	menuNode* currentMenu = menu_init();
	menuNode* mainMenu = currentMenu;
	
	interrupt CAN_interrupt = noInt;
	
	uint8_t mainLoopCounter = 0;
	
	GameState gameState;
	gameState.useJSnotSENS = 1;
	gameState.points = 0;
	gameState.currentStatus = pause;
	EEPROM_read_gamestate(&gameState);
	
	
	/*Can variables*/
	//The length variable indicates if the message is unhandeled.
	//After the message is handled the length variable must be set to 0
	//to prevent repeated actions.
	//The information in the message shall be kept until a new message
	//has arrived or is ready to send. 
	
	//Shell for motor signals
	CAN_message canMsgMotor;
	canMsgMotor.length = 0; //Also indicates an uptadate that needs to be sent
	canMsgMotor.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_MOTORSIGNALS;
	canMsgMotor.data[CANMSG_BTNR_BYTE] = 0;
	canMsgMotor.data[CANMSG_SLIDERR_BYTE] = 0;
	canMsgMotor.data[CANMSG_JSX_BYTE] = 0;
	canMsgMotor.id = NODE2_CANID_0;
	
	//Shell for game mode signals
	CAN_message canMsgGameMode;
	canMsgGameMode.length = 0; //Also indicating an update needing to be sent
	canMsgGameMode.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_GAMEMODE;
	canMsgGameMode.id = NODE2_CANID_HIGHPRIO_0;
	
	//Input message from node 2
	CAN_message canMsgInn;
	canMsgInn.length = 0; //Also indicates new message
	
	printf("ALL INIT complete");
	//printf("\n\n\n");
    while(1){
		/*State update*/
		controllers_update(&controls);
		CAN_interrupt = CAN_int();
		
		/*Can message handling*/
		switch(CAN_interrupt){
			case noInt:
				break;
			case err:
				printf("CAN error");
				break;
			case rx0:
				CAN_data_receive(&canMsgInn, MCP_RXB0CTRL);
				break;
			case rx1:
				CAN_data_receive(&canMsgInn, MCP_RXB1CTRL);
				break;
		}
		CAN_int_clear(CAN_interrupt);

 		/*Menu*/
 		//Each menu state function returns whether we want to return to main menu or not.
		if(controls.btnL.edge){
			//BtnL will always take us back to the main menu
			currentMenu = mainMenu;
		}
		switch (currentMenu->currentState){
			case menu:
				menu_go(&currentMenu, &controls);
				//If we have not sent a message requesting node 2 to turn of the game
				if(canMsgGameMode.data[GAMEMODE_MODE_BYTE] != GAMEMODE_OFF){
					//then send this message
					canMsgGameMode.length = GAMEMODE_MSGLEN;
					canMsgGameMode.data[GAMEMODE_MODE_BYTE] = GAMEMODE_OFF;	
				}
				break;
			case runGame:
				//Reqests to send a gameMode update if it has happned.
				if(gameState.useJSnotSENS == 1 && canMsgGameMode.data[GAMEMODE_MODE_BYTE] != GAMEMODE_JS){
					canMsgGameMode.length = GAMEMODE_MSGLEN;
					canMsgGameMode.data[GAMEMODE_MODE_BYTE] = GAMEMODE_JS;
				}
				else if(gameState.useJSnotSENS == 0 && canMsgGameMode.data[GAMEMODE_MODE_BYTE] != GAMEMODE_SENS){
					canMsgGameMode.length = GAMEMODE_MSGLEN;
					canMsgGameMode.data[GAMEMODE_MODE_BYTE] = GAMEMODE_SENS;
				}
				//Runs the game which also sends motor signals
				if(run_game(&gameState,&controls,&canMsgMotor,&canMsgInn)){
					currentMenu = mainMenu;
				}
				break;
			case highScore:
				if(displayHighScore(&gameState,&controls)){
					currentMenu = mainMenu;
				}
				break;
			case calibrateJS:
				if(joystick_user_calibrate(&controls)){
					currentMenu = mainMenu;
				}
				break;
			case controllerJS:
				gameState.useJSnotSENS = 1;
				currentMenu = mainMenu;
				break;
			case controllerSens:		
				gameState.useJSnotSENS = 0;
				currentMenu = mainMenu;
				break;
			case deleteHS:
				//Resets eeprom
				eeprom_write_byte(EEPROM_HIGHSCOREBYTE,0);
				if(NAME_LEN > 3){
					eeprom_write_byte(EEPROM_HIGHSCORENAME+0,'N'-asciiOffset);
					eeprom_write_byte(EEPROM_HIGHSCORENAME+1,'A'-asciiOffset);
					eeprom_write_byte(EEPROM_HIGHSCORENAME+2,'N'-asciiOffset);
					for(uint8_t i=3;i<NAME_LEN;++i){
						eeprom_write_byte(EEPROM_HIGHSCORENAME+i,0);
					}
				}
				else{
					for(uint8_t i=3;i<NAME_LEN;++i){
						eeprom_write_byte(EEPROM_HIGHSCORENAME+i,0);
					}
				}
				//Realods eeprom from highscore
				EEPROM_read_gamestate(&gameState);

				currentMenu = mainMenu;
				break;
		}
		
		
				
		
		//60hz tasks
		if(TCNT3 > (F_CPU/(8*60))){
			mainLoopCounter++;
			if(!(mainLoopCounter%60)){
				toggle_bit(LED_PORT, LED_BIT);
				if (gameState.currentStatus == play && currentMenu->currentState == runGame){
					gameState.points++;
				}
			}
			
			//If the can message has a length, then it is requesting to be sent
			if(canMsgGameMode.length){
				CAN_message_send(&canMsgGameMode);
				canMsgGameMode.length = 0;
			}
			if(canMsgMotor.length){
				CAN_message_send(&canMsgMotor);
				canMsgMotor.length = 0;
				
				if(canMsgMotor.data[CANMSG_BTNR_BYTE]){
					puts("PUSH!");
				}
			}
			OLED_update_screen();
			TIMER_60HZ_RESET;
		}
    }
}