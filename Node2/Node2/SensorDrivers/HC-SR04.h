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

#define S0_ECHO_INTERRUPT_BIT ISC20
#define S1_ECHO_INTERRUPT_BIT ISC30

#define ETIMER_MEASURE TCNT4
#define ETIMER_MEASURE_PRESCALER_VAL 8
#define ETIMER_MEASURE_PRESCALER_BIT 0b010
#define ETIMER_MEASURE_DISABLE (TCCR4B &= ~(0b111 << CS40))
#define ETIMER_MEASURE_ENABLE (TCCR4B |= ETIMER_MEASURE_PRESCALER_BIT << CS40)
#define ETIMER_MEASURE_ENABLE_READ (TCCR4B & (0b111<<CS40))
#define ETIMER_MEASURE_RESET (TCNT4 = 0)

#define ETIMER_TRIGGER TCNT5
#define ETIMER_TRIGGER_PRESCALER_VAL 64
#define ETIMER_TRIGGER_PRESCALER_BIT 0b011
#define ETIMER_TRIGGER_DISABLE (TCCR5B &= ~(0b111 << CS50))
#define ETIMER_TRIGGER_ENABLE (TCCR5B |= ETIMER_MEASURE_PRESCALER_BIT << CS50)
#define ETIMER_TRIGGER_ENABLE_READ (TCCR5B & (0b111<<CS50))
#define ETIMER_TRIGGER_RESET (TCNT5 = 0)

#define ECHO_INTERRUPT_FALLING(edgeBit) clear_bit(EICRA, edgeBit)
#define ECHO_INTERRUPT_FALLING_READ(edgeBit) !(EICRA & (1<<edgeBit))
#define ECHO_INTERRUPT_RISING(edgeBit) clear_bit(EICRA, edgeBit)
#define ECHO_INTERRUPT_RISING_READ(edgeBit) EICRA & (1<<edgeBit)

#define ECHO_MEASUREMENT_INTERVAL 0.006f
#define ECHO_PRESCALER 8

#define ECHO_TRIGGERPULSEWIDTH_us 10

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

#define S1_ACTIVATION_DISTANCE 500

#define ECHO_DIST_FROM_MOTOR0 4
#define uS_PER_CM 58


#define ECHO_averagingPeriod 3
#define ECHO_MAX_DEVIATION_ENCODER_DIST 3000
typedef struct ECHO_data{
	int16_t pos_ref;
	uint8_t queuePointer;
	uint32_t sum;
	uint16_t mesurements[ECHO_averagingPeriod];
}ECHO_data;

void echo_init();
void echo_data_init(ECHO_data* data);
uint8_t echo_measure(uint8_t sensorID);
void echo_update_ref(ECHO_data* data, uint8_t sensorId, uint8_t edgeBit);
int32_t echo_time_to_encoder_val(uint16_t time);
void handleInterrupt(uint8_t timerId, uint8_t edgeBit);
#endif /* HC-SR04_H_ */
