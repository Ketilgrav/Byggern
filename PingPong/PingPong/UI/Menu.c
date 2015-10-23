/*
* Menu.c
*
* Created: 25.09.2015 09:29:08
*  Author: sverrevr
*/

#include "../Drivers/Controllers.h"
#include "../Drivers/OLED.h"
#include "Menu.h"

menyNode mainMenu;
menyNode options;
menyNode reCalibrateJs;
menyNode newGame;
menyNode highScore;
menyNode canMsg;

menyNode* menu_init(){
// 	menyNode* mainMenu = (menyNode*) malloc(sizeof(menyNode));
// 	menyNode* options = (menyNode*) malloc(sizeof(menyNode));
// 	menyNode* reCalibrateJs = (menyNode*) malloc(sizeof(menyNode));
// 	menyNode* newGame = (menyNode*) malloc(sizeof(menyNode));
// 	menyNode* highScore = (menyNode*) malloc(sizeof(menyNode));
	
	
	strcpy(options.tekst,			"Options       ");
	strcpy(newGame.tekst,			"New Game      ");
	strcpy(highScore.tekst,			"High scores   ");
	strcpy(mainMenu.tekst,			"Main menu!    ");
	strcpy(reCalibrateJs.tekst,		"Re calib. js. ");
	strcpy(canMsg.tekst,			"Disp. CAN msg.");
	
	mainMenu.forelder = NULL;
	mainMenu.nBarn = 4;
	mainMenu.barn[0] = &options;
	mainMenu.barn[1] = &newGame;
	mainMenu.barn[2] = &highScore;
	mainMenu.barn[3] = &canMsg;
	mainMenu.pilNivaa = 1;
	mainMenu.tilstand = MENU;
	
	options.forelder = &mainMenu;
	options.nBarn = 1;
	options.barn[0] = &reCalibrateJs;
	options.pilNivaa = 1;
	options.tilstand = MENU;
	
	reCalibrateJs.forelder = &options;
	reCalibrateJs.nBarn = 0;
	reCalibrateJs.pilNivaa = 1;
	reCalibrateJs.tilstand = CALIBRATE_JS;
	
	newGame.forelder = &mainMenu;
	newGame.nBarn = 0;
	newGame.pilNivaa = 1;
	newGame.tilstand = RUN_GAME;
	
	highScore.forelder = &mainMenu;
	highScore.nBarn = 0;
	highScore.pilNivaa = 1;
	highScore.tilstand = HIGH_SCORE;
	
	canMsg.forelder = &mainMenu;
	canMsg.nBarn = 0;
	canMsg.pilNivaa = 1;
	canMsg.tilstand = SHOW_CAN_MSG;
	
	return &mainMenu;
	
}

void menu_go(menyNode** meny, JoyStick* js){
	flyttPil(&((*meny)->pilNivaa), js, (*meny)->nBarn);
	
	oled_mem_clear();
	oled_mem_print((*meny)->tekst,0,0);

	for(int i=1; i<=(*meny)->nBarn; ++i){
		if((*meny)->pilNivaa == i){
			oled_mem_print("-s",i,0);
		}
		else{
			oled_mem_print("  ",i,0);
		}
		oled_mem_print((*meny)->barn[i-1]->tekst,i,2);
	}
	if(js->x_descreet_edge > 0){
		if((*meny)->pilNivaa !=0  &&((*meny)->pilNivaa <= (*meny)->nBarn)){
			*meny = (*meny)->barn[((*meny)->pilNivaa)-1];
		}
	}
	else if(js->x_descreet_edge < 0){
		if((*meny)->forelder != NULL){
			*meny = (*meny)->forelder;
		}
	}
}

void flyttPil(uint8_t* nivaa, JoyStick* js, uint8_t nBarn){
	if(js->y_descreet_edge == 0){
		return;
	}
	(*nivaa) -= js->y_descreet;
	if((*nivaa) <1) *nivaa = nBarn;
	else if((*nivaa) > nBarn) *nivaa = 1;
}