/*
 * Game.h
 *
 * Created: 25.09.2015 16:51:59
 *  Author: sverrevr
 */ 


#ifndef GAME_H_
#define GAME_H_
#include "../MainInclude.h"
#include "../Drivers/Controllers.h"
#include "../CommunicationDrivers/can.h"
#include "../Drivers/OLED.h"

typedef enum state { play = 0, gameOver = 1, pause = 2, prePause = 3 } status;

#define NAME_LEN 3
typedef struct GameState{
	uint8_t useJSnotSENS;
	uint16_t points;
	uint16_t record;
	char name[NAME_LEN+1]; //+1 for '\0'
	uint8_t namePointer;
	status currentStatus;
} GameState;

uint8_t run_game(GameState* gameState, Controls* controls, CAN_message* msgMtor, CAN_message* msgGame);
void update_name(GameState* gameState, Controls* controls);

#endif /* GAME_H_ */