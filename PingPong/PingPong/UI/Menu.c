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

//Generating the menu states, without allocating memory manually. 
menuNode mainMenu;
menuNode options;
menuNode reCalibrateJs;
menuNode chooseController;
menuNode controllerJoystick;
menuNode controllerSensor;
menuNode newGame;
menuNode highScore;
menuNode canMsg;

menuNode* menu_init(){
	strcpy(options.text,			"Options       ");
	strcpy(newGame.text,			"New Game      ");
	strcpy(highScore.text,			"High scores   ");
	strcpy(mainMenu.text,			"Main menu!    ");
	strcpy(reCalibrateJs.text,		"Re calib. js. ");
	strcpy(canMsg.text,				"Disp. CAN msg.");
	strcpy(chooseController.text,	"Choose cntrlr.");
	strcpy(controllerJoystick.text,	"Joystick      ");
	strcpy(controllerSensor.text,	"Sensor        ");
	
	mainMenu.parent = NULL;
	mainMenu.nChildren = 4;
	mainMenu.child[0] = &options;
	mainMenu.child[1] = &newGame;
	mainMenu.child[2] = &highScore;
	mainMenu.child[3] = &canMsg;
	mainMenu.arrowLevel = 1;
	mainMenu.currentState = MENU;
	
	options.parent = &mainMenu;
	options.nChildren = 2;
	options.child[0] = &reCalibrateJs;
	options.child[1] = &chooseController;
	options.arrowLevel = 1;
	options.currentState = MENU;
	
	reCalibrateJs.parent = &options;
	reCalibrateJs.nChildren = 0;
	reCalibrateJs.arrowLevel = 1;
	reCalibrateJs.currentState = CALIBRATE_JS;
	
	chooseController.parent = &options;
	chooseController.nChildren = 2;
	chooseController.child[0] = &controllerJoystick;
	chooseController.child[1] = &controllerSensor;
	chooseController.arrowLevel = 1;
	chooseController.currentState = MENU;
	
	controllerJoystick.parent = &chooseController;
	controllerJoystick.nChildren = 0;
	controllerJoystick.arrowLevel = 1;
	controllerJoystick.currentState = CNTRL_JS;
	
	controllerSensor.parent = &chooseController;
	controllerSensor.nChildren = 0;
	controllerSensor.arrowLevel = 1;
	controllerSensor.currentState = CNTRL_SENS;
	
	newGame.parent = &mainMenu;
	newGame.nChildren = 0;
	newGame.arrowLevel = 1;
	newGame.currentState = RUN_GAME;
	
	highScore.parent = &mainMenu;
	highScore.nChildren = 0;
	highScore.arrowLevel = 1;
	highScore.currentState = HIGH_SCORE;
	
	canMsg.parent = &mainMenu;
	canMsg.nChildren = 0;
	canMsg.arrowLevel = 1;
	canMsg.currentState = SHOW_CAN_MSG;
	
	return &mainMenu;
	
}

void menu_go(menuNode** menu, Controls* control){
	//moves the arrow according to joystick
	flyttPil(&((*menu)->arrowLevel), &control->jsY, (*menu)->nChildren);
	
	oled_clear();
	//Prints the title
	oled_print((*menu)->text,0,0);
	
	//Iterates through submenus and prints them
	for(int i=1; i<=(*menu)->nChildren; ++i){
		//Prints a spaceinvader at the current arrow level.
		if((*menu)->arrowLevel == i){
			oled_print("-s",i,0);
		}
		else{
			oled_print("  ",i,0);
		}
		oled_print((*menu)->child[i-1]->text,i,2);
	}
	
	//Left/right joystick changes the menu level. 
	//Go to the child currently pointed at
	if(control->jsX.descreet_edge > 0){
		if((*menu)->arrowLevel !=0  &&((*menu)->arrowLevel <= (*menu)->nChildren)){
			*menu = (*menu)->child[((*menu)->arrowLevel)-1];
		}
	}
	//Go to parent
	else if(control->jsX.descreet_edge < 0){
		if((*menu)->parent != NULL){
			*menu = (*menu)->parent;
		}
	}
}

void flyttPil(uint8_t* level, JoyStick* jsY, uint8_t nChildren){
	if(jsY->descreet_edge == 0){
		//Nothing has been pressed, do nothing
		return;
	}
	//Moves according to joystick
	(*level) -= jsY->descreet;
	if((*level) <1) *level = nChildren;			//If we are at the last element, go to first.
	else if((*level) > nChildren) *level = 1;	//If we are at the first element, go to last.
}