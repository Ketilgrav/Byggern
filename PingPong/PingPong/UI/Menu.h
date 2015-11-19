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

typedef enum menuState { menu = 0, runGame, highScore, calibrateJS, controllerJS, controllerSens, deleteHS} menuState;

typedef struct menuNode{
	menuState currentState;
	uint8_t nChildren;
	uint8_t arrowLevel;
	char text[16];
	struct menuNode* parent;
	struct menuNode* child[7];
}menuNode;

menuNode* menu_init();
void menu_go(menuNode** menu, Controls* controls);
void move_arrow(uint8_t* level, JoyStick* js, uint8_t nChildren);

#endif /* MENU_H_ */