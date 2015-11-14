/*
 * Menu.h
 *
 * Created: 25.09.2015 09:28:47
 *  Author: sverrevr
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "../Drivers/Controllers.h"
#include "../MainInclude.h"

enum Tilstand {MENU = 0, RUN_GAME = 1, HIGH_SCORE = 2, CALIBRATE_JS=3, SHOW_CAN_MSG=4, CNTRL_JS=5, CNTRL_SENS=6};

typedef struct menyNode{
	enum Tilstand tilstand;
	uint8_t nBarn;
	uint8_t pilNivaa;
	char tekst[16];
	struct menyNode* forelder;
	struct menyNode* barn[7];
}menyNode;

menyNode* menu_init();
void menu_go(menyNode** meny, Controls* controls);
void flyttPil(uint8_t* nivaa, JoyStick* js, uint8_t nBarn);

#endif /* MENU_H_ */