/*
 * Game.c
 *
 * Created: 25.09.2015 16:51:47
 *  Author: sverrevr
 */

#include "Game.h"
uint8_t runGame(GameState* gameState, Controls* controls, CAN_message* msgMtor, CAN_message* msgGame){
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
			gameState->status = gameOver;
		}
		else if (msgGame->data[GAMESIGNAL_SIGNAL_BYTE] == GAMESIGNAL_START && gameState->status == pause){
			gameState->status = play;
			gameState->points = 0;
		}
		msgGame->length = 0;
	}


	oled_clear();
	switch (gameState->status){
		//Waiting to start game
		case pause:
			oled_print("NYTT SPILL", 1, 0);
			oled_print("DIN KONTROLLER:", 3, 0);
			if (gameState.useJSnotSENS){
				oled_print("JOYSTICK", 4, 0);
			}
			else{
				oled_print("SENSOR", 4, 0);
			}
			oled_print("START SPILL VED", 6, 0);
			oled_print("   AA SKYTE", 7, 0);
			break
	
		//Running game
		case play:
			oled_print("SPILLET KJØRER", 1, 0);

			oled_print("POENG:", 3, 0);
			char currentPoints[5];
			sprintf(currentPoints, "%u", gameState->points);
			oled_print(currentPoints, 3, 9);

			oled_print("REKORD:", 5, 0);
			char recordPoints[5];
			sprintf(recordPoints, "%u", gameState->record);
			oled_print(recordPoints, 5, 9);
			break

		//Game over
		case gameOver:
			if (gameState->points > gameState->record){
				gameState->record = gameState->points;
				eeprom_write_byte(EEPROM_HIGHSCOREBYTE,gameState->record);
			}
			if (gameState->points >= gameState->record){
				oled_print("NY REKORD!", 0, 0);
				oled_print("GRATULERER!", 1, 0);
			}
			else{
				oled_print("DU TAPTE!", 1, 0);
			}

			oled_print("POENG:", 3, 0);
			char currentPoints[5];
			sprintf(currentPoints, "%u", gameState->points);
			oled_print(currentPoints, 3, 9);

			oled_print("REKORD:", 5, 0);
			char recordPoints[5];
			sprintf(recordPoints, "%u", gameState->record);
			oled_print(recordPoints, 5, 9);

			oled_print("RESTART MED A", 7, 0);

			//START PÅ NYTT
			if (controls->btnR.edge){
				gameState->status = pause;
			}
			
			break
		default:
			break;
		}


	
	

	char c[5];
	sprintf(c, "%u", gameState->points);
	oled_print(c, 6, 0);
	
	oled_clear();
	oled_print("SPILLET KJORER", 3, 0);
	char a[5];
	sprintf(a, "%i", controls->jsX.percent);
	char b[5];
	sprintf(b, "%i", controls->jsY.percent);
	oled_print(a, 4, 0);
	oled_print(b, 5, 0);



	return 0;
}



//TULLL
