/*
* Menu.c
*
* Created: 25.09.2015 09:29:08
*  Author: sverrevr
*/

#include "../Drivers/Controllers.h"
#include "../Drivers/OLED.h"
#include "Menu.h"
#include "../../../InterNodeHeaders/CanMessageFormat.h"
#include "../Communication_drivers/can.h"

//Genererer manytillstandene, uten å alokere minnet manuelt. 
menyNode mainMenu;
menyNode options;
menyNode reCalibrateJs;
menyNode chooseController;
menyNode controllerJoystick;
menyNode controllerSensor;
menyNode newGame;
menyNode highScore;
menyNode canMsg;

menyNode* menu_init(){
	strcpy(options.tekst,			"Options       ");
	strcpy(newGame.tekst,			"New Game      ");
	strcpy(highScore.tekst,			"High scores   ");
	strcpy(mainMenu.tekst,			"Main menu!    ");
	strcpy(reCalibrateJs.tekst,		"Re calib. js. ");
	strcpy(canMsg.tekst,			"Disp. CAN msg.");
	strcpy(chooseController.tekst,	"Choose cntrlr.");
	strcpy(controllerJoystick.tekst,"Joystick      ");
	strcpy(controllerSensor.tekst,	"Sensor        ");
	
	mainMenu.forelder = NULL;
	mainMenu.nBarn = 4;
	mainMenu.barn[0] = &options;
	mainMenu.barn[1] = &newGame;
	mainMenu.barn[2] = &highScore;
	mainMenu.barn[3] = &canMsg;
	mainMenu.pilNivaa = 1;
	mainMenu.tilstand = MENU;
	
	options.forelder = &mainMenu;
	options.nBarn = 2;
	options.barn[0] = &reCalibrateJs;
	options.barn[1] = &chooseController;
	options.pilNivaa = 1;
	options.tilstand = MENU;
	
	reCalibrateJs.forelder = &options;
	reCalibrateJs.nBarn = 0;
	reCalibrateJs.pilNivaa = 1;
	reCalibrateJs.tilstand = CALIBRATE_JS;
	
	chooseController.forelder = &options;
	chooseController.nBarn = 2;
	chooseController.barn[0] = &controllerJoystick;
	chooseController.barn[1] = &controllerSensor;
	chooseController.pilNivaa = 1;
	chooseController.tilstand = MENU;
	
	controllerJoystick.forelder = &chooseController;
	controllerJoystick.nBarn = 0;
	controllerJoystick.pilNivaa = 1;
	controllerJoystick.tilstand = CNTRL_JS;
	
	controllerSensor.forelder = &chooseController;
	controllerSensor.nBarn = 0;
	controllerSensor.pilNivaa = 1;
	controllerSensor.tilstand = CNTRL_SENS;
	
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

void menu_go(menyNode** meny, Controls* control){
	//Flytter pilen ihht joystick
	flyttPil(&((*meny)->pilNivaa), &control->jsY, (*meny)->nBarn);
	
	oled_clear();
	//Skriver ut tittelen
	oled_print((*meny)->tekst,0,0);
	
	//Går gjennom alle undermenyene og skriver dem ut.
	for(int i=1; i<=(*meny)->nBarn; ++i){
		//skriver ut spaceinvader for å vise nivået brukeren peker på
		if((*meny)->pilNivaa == i){
			oled_print("-s",i,0);
		}
		else{
			oled_print("  ",i,0);
		}
		oled_print((*meny)->barn[i-1]->tekst,i,2);
	}
	
	//Høyre/venstre på joystick endrer menynivå. 
	//gå til barnet vi peker på
	if(control->jsX.descreet_edge > 0){
		if((*meny)->pilNivaa !=0  &&((*meny)->pilNivaa <= (*meny)->nBarn)){
			*meny = (*meny)->barn[((*meny)->pilNivaa)-1];
		}
	}
	//Gå til forelderen
	else if(control->jsX.descreet_edge < 0){
		if((*meny)->forelder != NULL){
			*meny = (*meny)->forelder;
		}
	}
}

void flyttPil(uint8_t* nivaa, JoyStick* jsY, uint8_t nBarn){
	if(jsY->descreet_edge == 0){
		//Har ikke trykket, da skal den ikke flyttes
		return;
	}
	//Flytter utifra joystick
	(*nivaa) -= jsY->descreet;
	if((*nivaa) <1) *nivaa = nBarn;			//Om vi er før første element underflower vi til siste
	else if((*nivaa) > nBarn) *nivaa = 1;	//etter siste overflower vi til første.
}