/*
 * EEPROM.c
 *
 * Created: 19.11.2015 14.43.32
 *  Author: sverre
 */ 

#include "EEPROM.h"
void EEPROM_read_gamestate(GameState* gameState){
// 	gameState->record = eeprom_read_byte(EEPROM_HIGHSCOREBYTE);
// 	for(uint8_t i=0; i<NAME_LEN; ++i){
// 		gameState->name[i] = eeprom_read_byte(EEPROM_HIGHSCORENAME+i);
// 	}
	gameState->name[NAME_LEN] = '\0';
	gameState->name[0] = 'k';
	gameState->name[1] = 'e';
	gameState->name[2] = 't';
	gameState->record = 5;
}