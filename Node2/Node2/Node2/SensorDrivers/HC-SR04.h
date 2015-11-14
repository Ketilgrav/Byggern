/*
 * HC_SR04.h
 *
 * Created: 14.11.2015 14:24:02
 *  Author: sverrevr
 */ 


#ifndef HC_SR04_H_
#define HC_SR04_H_
#include "../MainInclude.h"


#define HCSR04_TRIGGERPULSEWIDTH_us 10
#define HCSR04_TRIG_DDR DDRC
#define HCSR04_ECHO_DDR DDRC
#define HCSR04_TRIG_PORT PORTC
#define HCSR04_ECHO_PIN PINC
#define HCSR04_TRIG_BIT PC7
#define HCSR04_ECHO_BIT PC6

#define HCSR04_MAX_TIME 2321
#define HCSR04_MIN_TIME 174
#define HCSR04_SCALER 3.8f
#define HCSR04_ZERO_POINT 4400

/*
Boks 40cm
40cm -> 2320us

gang med 3,8 for verdier fra 0-8.800
*/


#define HCSR04_averagingPeriod 10
//#define HCSR04_MAX_DEVIATION 500
typedef struct HCSR04_data{
	int16_t pos_ref;
	uint8_t queuePointer;
	uint16_t mesurements[HCSR04_averagingPeriod];
}HCSR04_data;

void HCSR04_inti();
uint16_t HCSR04_measure();
void HCSR04_update_ref(HCSR04_data* data);

#endif /* HC-SR04_H_ */
