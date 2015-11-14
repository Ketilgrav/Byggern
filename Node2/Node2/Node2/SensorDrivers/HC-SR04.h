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
#define HCSR04_TRIG_DDR
#define HCSR04_ECHO_DDR
#define HCSR04_TRIG_PORT
#define HCSR04_ECHO_PIN
#define HCSR04_TRIG_BIT
#define HCSR04_ECHO_BIT

#define HCSR04_MAX_TIME
#define HCSR04_MIN_TIME
#define HCSR04_SCALER
#define HCSR04_ZERO_POINT

void HCSR04_inti();
uint8_t HCSR04_measure();
void HCSR04_update_ref(uint8_t* posRef);

#endif /* HC-SR04_H_ */
