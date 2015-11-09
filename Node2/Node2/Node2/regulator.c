/*
 * regulator.c
 *
 * Created: 06.11.2015 11:02:05
 *  Author: sverrevr
 */ 
#include "regulator.h"

void regulator_init(PI* pi_state){
	pi_state->P = 4;
	pi_state->I = 1;
	pi_state->u= 0;
	//pi_state->MillionIntegralValue = 0;
	
	/* Setter opp klokken som beregner tiden mellom hver incrementering*/
	//Bruker timer/counter 3 med normal opperation
	//TCCR3B |= (1<<CS10); //aktiverer, med clock/1 prescaler. Kan da telle i 4ms, dette er for lite?
	//TCNT3 holder verdien, resettes ved å sette den lik 0;	
}

void regulator_increment(PI* pi_state, int8_t ref_percent){
	int16_t refPos = get_pos_from_percent(ref_percent);
	int16_t encoderPos = motorbox_get_encoder();
	int16_t avvik = (refPos-encoderPos)/(board_size/100); //I prosent, -100er motor helt til høyre, mens vi vil helt til venstre
	//pi_state->MillionIntegralValue+=avvik*TCNT3/(F_CPU/1000000);	
	printf("Ref: %i   \tEncoder: %i    \tAvvik: %i    \r", refPos,encoderPos,avvik);
	//TCNT3 = 0;
	//Definerer brettet som venstre -4400, høyre 4400, encoder er fikset til å gi ut dette
	//u_val = oversett refferansen  til possisjon - encoderen
	//Må gjøre om til prosent siden det er det vi sender inn i motor power
	//u_val = u_val / (board_Size/100) Må gjøre dobbelt deltpå ellers blir det overfloat på regnestykket elrns
	//Så ganger vi det med P.
	
	//Feil: Innimellom blir det fuck fuck. Kanskje siden den matten ikke funker (slik som at vi måtte / (board_size)/100
	//Fuckfuck skjer når vi ikke flytter kontinuerlig? Altså gjør ett hopp på slider?
	//Feil: Motoren flytter seg ikke med mindre enn 50 feil.
	
	//Oppgradering: implementer I.
	
	//Oversetter refferansen til 
	pi_state->u =  avvik /** pi_state->P*/ /*+ pi_state->MillionIntegralValue/1000000 * pi_state->I*/;
}
int16_t get_pos_from_percent(int8_t percent){
	return (board_size/200) * percent;
}