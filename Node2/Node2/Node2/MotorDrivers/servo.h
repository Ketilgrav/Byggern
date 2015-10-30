/*
 * servo.h
 *
 * Created: 23.10.2015 09:09:29
 *  Author: sverrevr
 */ 


#ifndef SERVO_H_
#define SERVO_H_

//Bruker timer 1, register A

#define duty_cycle_ms (20.0/1000.0)
#define pulse_width_min (0.9/1000.0)
#define pulse_width_neutral (1.5/1000.0)
#define pulse_width_max (2.1/1000.0)


#define CLK0 0b000
#define CLK1 0b001
#define CLK8 0b010
#define CLK64 0b011
#define CLK256 0b100
#define CLK1024 0b101
#define clock_scaler CLK8
#define clock_scaler_val 8

#define PWM_PORT PORTB
#define PWM_PIN PINB
#define PWM_DDR DDRB
#define PWM_bit PB5

void servo_init();
void servo_set(int percent);


#endif /* SERVO_H_ */