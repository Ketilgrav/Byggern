/*
 * main.h
 *
 * Created: 19.11.2015 23:33:39
 *  Author: sverrevr
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#define STIMER_PRESCALER_VAL 1024
#define STIMER_PRESCALER 0b101
#define STIMER_ACTIVATE (TCCR0B |= (STIMER_PRESCALER<<CS00))
#define STIMER_DEACTIVATE (TCCR0B &= (0b111<<CS00))
#define STIMER_OVERFLOW_TEST (TIFR0 & TOV0)
#define STIMER_OVERFLOW_RESET (TIFR0 |= 1<<TOV0)
#define STIMER_RESET (TCNT0 = 0)



#endif /* MAIN_H_ */