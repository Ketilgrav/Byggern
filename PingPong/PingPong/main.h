/*
 * main.h
 *
 * Created: 19.11.2015 10.06.10
 *  Author: sverre
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define TIMER_60HZ TCNT3
#define TIMER_60HZ_PRESCALER_VAL 8
#define TIMER_60HZ_PRESCALER 0b010
#define TIMER_60HZ_ACTIVATE (TCCR3B |= (TIMER_60HZ_PRESCALER<<CS30))
#define TIMER_60HZ_RESET (TIMER_60HZ = 0)


#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_BIT PB0


#endif /* MAIN_H_ */