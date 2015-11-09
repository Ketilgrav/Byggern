/*
 * Game.h
 *
 * Created: 25.09.2015 16:51:59
 *  Author: sverrevr
 */ 


#ifndef GAME_H_
#define GAME_H_
#include "../MainInclude/MainInclude.h"
#include "../Drivers/Controllers.h"
#include "../Communication_drivers/can.h"
#include "../../../InterNodeHeaders/CanMessageFormat.h"
#include "../Communication drivers/can.h"
uint8_t runGame(Controls* controls, CAN_message* msgOut);



#endif /* GAME_H_ */