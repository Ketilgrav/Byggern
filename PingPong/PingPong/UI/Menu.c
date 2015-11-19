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
#include "../CommunicationDrivers/can.h"

//Generating the menu states, without allocating memory manually. 
menuNode mainMenu;
menuNode dispHighScore;
menuNode newGame;
menuNode options;
menuNode reCalibrateJs;
menuNode deleteHighScore;
menuNode chooseController;
menuNode controllerJoystick;
menuNode controllerSensor;

menuNode* menu_init(){
	strcpy(options.text,			"Options       ");
	strcpy(newGame.text,			"New Game      ");
	strcpy(dispHighScore.text,			"High scores   ");
	strcpy(mainMenu.text,			"Main menu!    ");
	strcpy(reCalibrateJs.text,		"Re calib. js. ");
	strcpy(chooseController.text,	"Choose cntrlr.");
	strcpy(controllerJoystick.text,	"Joystick      ");
	strcpy(controllerSensor.text,	"Sensor        ");
	strcpy(deleteHighScore.text,			"Delete H.S.   ");
	
	mainMenu.parent = NULL;
	mainMenu.nChildren = 3;
	mainMenu.child[0] = &options;
	mainMenu.child[1] = &newGame;
	mainMenu.child[2] = &dispHighScore;
	mainMenu.arrowLevel = 1;
	mainMenu.currentState = menu;
	
	options.parent = &mainMenu;
	options.nChildren = 3;
	options.child[0] = &reCalibrateJs;
	options.child[1] = &chooseController;
	options.child[2] = &deleteHighScore;
	options.arrowLevel = 1;
	options.currentState = menu;
	
	reCalibrateJs.parent = &options;
	reCalibrateJs.nChildren = 0;
	reCalibrateJs.arrowLevel = 1;
	reCalibrateJs.currentState = calibrateJS;
	
	deleteHighScore.parent = &options;
	deleteHighScore.nChildren = 0;
	deleteHighScore.arrowLevel = 1;
	deleteHighScore.currentState = deleteHS;
	
	chooseController.parent = &options;
	chooseController.nChildren = 2;
	chooseController.child[0] = &controllerJoystick;
	chooseController.child[1] = &controllerSensor;
	chooseController.arrowLevel = 1;
	chooseController.currentState = menu;
	
	controllerJoystick.parent = &chooseController;
	controllerJoystick.nChildren = 0;
	controllerJoystick.arrowLevel = 1;
	controllerJoystick.currentState = controllerJS;
	
	controllerSensor.parent = &chooseController;
	controllerSensor.nChildren = 0;
	controllerSensor.arrowLevel = 1;
	controllerSensor.currentState = controllerSens;
	
	newGame.parent = &mainMenu;
	newGame.nChildren = 0;
	newGame.arrowLevel = 1;
	newGame.currentState = runGame;
	
	dispHighScore.parent = &mainMenu;
	dispHighScore.nChildren = 0;
	dispHighScore.arrowLevel = 1;
	dispHighScore.currentState = highScore;
	
	return &mainMenu;
	
}

void menu_go(menuNode** menu, Controls* control){
	move_arrow(&((*menu)->arrowLevel), &control->jsY, (*menu)->nChildren);
	
	OLED_clear();
	OLED_print((*menu)->text,0,0);	//Prints the title
	
	//Iterates through submenues and prints them
	for(int i=1; i<=(*menu)->nChildren; ++i){
		//Prints a spaceinvader at the current arrow level.
		if((*menu)->arrowLevel == i){
			OLED_print("-s",i,0);
		}
		else{
			OLED_print("  ",i,0);
		}
		//The menu text is offset to the right by 2 to make room for the possible arrow
		OLED_print((*menu)->child[i-1]->text,i,2); 
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


/*Moves the menu indicator arrow according to the joystick descreet position*/
void move_arrow(uint8_t* level, JoyStick* jsY, uint8_t nChildren){
	if(jsY->descreet_edge == 0){
		//Nothing has been pressed, do nothing
		return;
	}
	//Moves according to joystick
	(*level) -= jsY->descreet;
	if((*level) <1) *level = nChildren;			//If we are at the last element, go to first.
	else if((*level) > nChildren) *level = 1;	//If we are at the first element, go to last.
}