/*
 * Menu.h
 *
 * Created: 25.09.2015 09:28:47
 *  Author: sverrevr
 */ 


#ifndef MENU_H_
#define MENU_H_

typedef struct menyNode{
	uint8_t nBarn;
	uint8_t pilNivaa;
	char tekst[8][16];
	struct menyNode* forelder;
	struct menyNode* barn[7];
}menyNode;

menyNode* menu_init();
void menu_print(menyNode* meny, JoyStick* js, uint8_t btnA, uint8_t btnB);
void flyttPil(uint8_t* nivaa, JoyStick* js, uint8_t nBarn);

#endif /* MENU_H_ */