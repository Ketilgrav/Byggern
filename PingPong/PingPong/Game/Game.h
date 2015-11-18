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
#include "../Communication_drivers/can.h"
#include "../Communication drivers/can.h"

enum status { play = 0, gameOver = 1, pause = 2 };

typedef struct GameState{
	uint8_t useJSnotSENS;
	uint16_t points;
	uint16_t record;
	status status;
} GameState;

uint8_t runGame(GameState* gameState, Controls* controls, CAN_message* msgOut, CAN_message* msgGame);


#endif /* GAME_H_ */