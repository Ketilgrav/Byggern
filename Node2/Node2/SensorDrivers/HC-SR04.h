/*
 * HC_SR04.h
 *
 * Created: 14.11.2015 14:24:02
 *  Author: sverrevr
 */ 


#ifndef HC_SR04_H_
#define HC_SR04_H_
#include "../MainInclude.h"
#include "../MotorDrivers/MotorBox.h"

#define HCSR04_MEASUREMENT_INTERVAL 0.002f
#define HCSR04_PRESCALER 8

#define HCSR04_TRIGGERPULSEWIDTH_us 10

#define SENSOR0 0
#define S0_TRIG_DDR DDRC
#define S0_ECHO_DDR DDRC
#define S0_TRIG_PORT PORTC
#define S0_ECHO_PIN PINC
#define S0_TRIG_BIT PC7
#define S0_ECHO_BIT PD2

#define SENSOR1 1
#define S1_TRIG_DDR DDRC
#define S1_ECHO_DDR DDRC
#define S1_TRIG_PORT PORTC
#define S1_ECHO_PIN PINC
#define S1_TRIG_BIT PC6
#define S1_ECHO_BIT PD3

#define S1_ACTIVATION_POINT 150

#define HCSR04_DIST_FROM_MOTOR0 4
#define uS_PER_CM 58


#define HCSR04_averagingPeriod 0
#define HCSR04_MAX_DEVIATION_ENCODER_DIST 1000
typedef struct HCSR04_data{
	int16_t pos_ref;
	uint8_t time;
	//uint8_t queuePointer;
	//uint8_t mesurements[HCSR04_averagingPeriod];
}HCSR04_data;

void HCSR04_inti();
uint8_t HCSR04_measure(uint8_t sensorID);
void HCSR04_update_ref(HCSR04_data* data, uint8_t sensorId);
int32_t echo_time_to_encoder_val(uint16_t time);

#endif /* HC-SR04_H_ */
