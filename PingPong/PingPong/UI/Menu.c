/*
 * Menu.c
 *
 * Created: 25.09.2015 09:29:08
 *  Author: sverrevr
 */ 

#include "../Drivers/Controllers.h"
#include "../Drivers/OLED.h"
#include "Menu.h"

menyNode* menu_init(){
	menyNode* mainMenu = (menyNode*) malloc(sizeof(menyNode));
	menyNode* options = (menyNode*) malloc(sizeof(menyNode));
	menyNode* newGame = (menyNode*) malloc(sizeof(menyNode));
	menyNode* highScore = (menyNode*) malloc(sizeof(menyNode));
	
	
	strcpy(options->tekst[0],   "Options       ");
	strcpy(newGame->tekst[0],   "New Game      ");
	strcpy(highScore->tekst[0], "High scores   ");
	strcpy(mainMenu->tekst[0],  "Main menu!    ");
	
	strcpy(mainMenu->tekst[1], options->tekst[0]);
	strcpy(mainMenu->tekst[2], newGame->tekst[0]);
	strcpy(mainMenu->tekst[3], highScore->tekst[0]);
	mainMenu->nBarn = 3;
	mainMenu->forelder = NULL;
	mainMenu->barn[0] = options;
	mainMenu->barn[1] = newGame;
	mainMenu->barn[2] = highScore;
	
	options->forelder = mainMenu;
	options->nBarn = 0;
	newGame->forelder = mainMenu;
	newGame->nBarn = 0;
	highScore->forelder = mainMenu;
	highScore->nBarn = 0;
	
	return mainMenu;
	
}

void menu_print(menyNode* meny, JoyStick* js, uint8_t btnA, uint8_t btnB){
	flyttPil(&(meny->pilNivaa), js, meny->nBarn);
	
	oled_goto_line(0);
	oled_print(meny->tekst[0]);
	for(int i=1; i<=meny->nBarn; ++i){
		oled_goto_line(i);
		if(meny->pilNivaa == i){
			oled_print("-s");	
		}
		else{
			oled_print("  ");
		}
		oled_print(meny->tekst[i]);
	}
	
	if(btnA){
		if(meny->pilNivaa <= meny->nBarn){
			meny = meny->barn[(meny->pilNivaa)-1];
			printf("%s", meny->tekst[0]);
		}
	}
	else if(btnB){
		if(meny->forelder != NULL){
			meny = meny->forelder;	
		}
	}
}

void flyttPil(uint8_t* nivaa, JoyStick* js, uint8_t nBarn){
	(*nivaa) -= js->y_descreet;
	if((*nivaa) <1) *nivaa = 1;
	else if((*nivaa) > nBarn) *nivaa = nBarn;
	
}