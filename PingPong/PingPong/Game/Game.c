/*
 * Game.c
 *
 * Created: 25.09.2015 16:51:47
 *  Author: sverrevr
 */

#include "Game.h"
uint8_t run_game(GameState* gameState, Controls* controls, CAN_message* msgMtor, CAN_message* msgGame){
	//printf("WTF MOTHERFUCKER?");
	//TRANSMITTING
	//Clear the solenoid push bit if message has been sent.
	if (msgMtor->length == 0){
		msgMtor->data[CANMSG_BTNR_BYTE] &= ~(1 << CANMSG_BTNR_BIT);
	}
	//Set the solenoid push bit if edge detected.
	if (controls->btnR.edge){
		msgMtor->data[CANMSG_BTNR_BYTE] |= 1 << CANMSG_BTNR_BIT;
	}
	//Send controller signals
	msgMtor->data[CANMSG_SLIDERR_BYTE] = controls->sliderR.percent;
	msgMtor->data[CANMSG_JSX_BYTE] = controls->jsX.percent;
	msgMtor->length = CANMSG_MOTORSIGNAL_LEN;

	//RECIEVEING
	if (msgGame->length && msgGame->data[CANMSG_PACKAGESPECIFIER] == PACKAGESPECIFIER_GAMESIGNAL){
		if (msgGame->data[GAMESIGNAL_SIGNAL_BYTE] == GAMESIGNAL_STOP){
			gameState->currentStatus = gameOver;
		}
		else if (msgGame->data[GAMESIGNAL_SIGNAL_BYTE] == GAMESIGNAL_START && gameState->currentStatus == pause){
			gameState->currentStatus = play;
			gameState->points = 0;
		}
		msgGame->length = 0;
	}

 	OLED_clear();
	switch (gameState->currentStatus){
		//Waiting to start game
		case pause:
			OLED_print("NYTT SPILL", 1, 0);
			OLED_print("DIN KONTROLLER:", 3, 0);
			if (gameState->useJSnotSENS){
				OLED_print("JOYSTICK", 4, 0);
			}
			else{
				OLED_print("SENSOR", 4, 0);
			}
			OLED_print("START SPILL VED", 6, 0);
			OLED_print("   AA SKYTE", 7, 0);
			break;
	
		//Running game
		case play:
			OLED_print("SPILLET KJORER", 1, 0);

			OLED_print("POENG:", 3, 0);
			char currentPoints[5];
			sprintf(currentPoints, "%u", gameState->points);
			OLED_print(currentPoints, 3, 9);

			OLED_print("REKORD:", 5, 0);
			char recordPoints[5];
			sprintf(recordPoints, "%u", gameState->record);
			OLED_print(recordPoints, 5, 9);
			break;

		//Game over
		case gameOver:
			if (gameState->points > gameState->record){
				gameState->record = gameState->points;
				OLED_print("GRARER!", 4, 0);
			}
			if (gameState->points >= gameState->record){
 				OLED_print("NY REKORD!", 0, 0);
 				OLED_print("GRATULERER!", 1, 0);
			}
			else{
 				OLED_print("DU TAPTE!", 1, 0);
 			}

			OLED_print("POINTS:", 3, 0);
			char pointString[5];
			sprintf(pointString, "%u", gameState->points);
			OLED_print(pointString, 3, 9);

			OLED_print("RECorD:", 5, 0);
			char recordString[5];
			sprintf(recordString, "%u", gameState->record);
			OLED_print(recordString, 5, 9);
 			OLED_print("RESTART MED A", 7, 0);

			//Updates and writes name.
			update_name(gameState, controls);
			OLED_print(gameState->name,2,0);

			//Restart, and save highscore and name if this was a new highscore
			if (controls->btnR.edge){
	// 			//If highscore:
	// 			if(gameState->points >= gameState->record){
	// 				eeprom_write_byte(EEPROM_HIGHSCOREBYTE,gameState->record);
	// 				for(uint8_t i= 0; i<NAME_LEN;++i){
	// 					eeprom_write_byte(EEPROM_HIGHSCORENAME+i,gameState->name[i]);
	// 				}
	// 			}
				gameState->currentStatus= pause;
			}
			break;
		default:
			break;
	}

	return 0;
}

void update_name(GameState* gameState, Controls* controls){
	//Move cursor left/right
	if(controls->jsX.descreet_edge > 0){
		gameState->namePointer++;
	}
	else if(controls->jsX.descreet_edge < 0){
		gameState->namePointer--;
	}
	
	//IF we moved past the last character
	if(gameState->namePointer == NAME_LEN){
		gameState->namePointer = 0;
	}
	//If we moved previous to the first, so that an overflow occurred
	else if(gameState->namePointer > NAME_LEN){
		gameState->namePointer = NAME_LEN-1;
	}
	
	//Change to next/previous char
	if(controls->jsY.descreet_edge > 0){
		gameState->name[gameState->namePointer]++;
	}
	else if(controls->jsY.descreet_edge < 0){
		gameState->name[gameState->namePointer]--;
	}
	//If we moved past font length
	if(gameState->name[gameState->namePointer] == FONT_SIZE){
		gameState->name[gameState->namePointer] = 0;
	}
	//If we moved previous to the first font sign, so that an overflow occurred
	else if(gameState->name[gameState->namePointer] > FONT_SIZE){
		gameState->name[gameState->namePointer] = FONT_SIZE-1;
	}
}