/*
 * MotorBox.h
 *
 * Created: 06.11.2015 08:35:54
 *  Author: sverrevr
 */ 


#ifndef MOTORBOX_H_
#define MOTORBOX_H_

#include "../MainInclude.h"
#include "../CommunicationDrivers/I2C.h"

#define BOARD_SIZE 8800
#define BOARD_SIZE_CM 40

#define MOTORBOX_CONTROLL_REG PORTF //MJ1
#define MOTORBOX_CONTROLL_DDR DDRF
#define	ENCODER_OUTPUTENABLE_NOT PF7
#define ENCODER_RESET_NOT PF6
#define ENCODER_SELECTHIGHBIT PF5
#define MOTOR_ENABLE PF4
#define MOTOR_DIRECTION PF3
#define MOTOR_SLACK_OFFSET 40
#define MOTOR_SLACK_TURNOFF 10


#define MOTORBOX_DATA_REG PORTK
#define MOTORBOX_DATA_PIN PINK
#define MOTORBOX_DATA_DDR DDRK


#define POS_DIR 1

void motorbox_init();
void motorbox_set_power(uint8_t dir, uint8_t power);
int16_t motorbox_get_encoder();
void motorbox_reset_encoder();
void motorbox_set_percent(int16_t percent);
uint8_t reverse_byte(uint8_t b);

#endif /* MOTORBOX_H_ */