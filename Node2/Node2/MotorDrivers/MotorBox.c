/*
 * MotorBOx.c
 *
 * Created: 06.11.2015 08:35:33
 *  Author: sverrevr
 */ 

#include "MotorBox.h"

void motorbox_init(){
	MOTORBOX_CONTROLL_DDR |= (1<<ENCODER_OUTPUTENABLE_NOT)|(1<<ENCODER_RESET_NOT)|(1<<ENCODER_SELECTHIGHBIT)|(1<<MOTOR_ENABLE)|(1<<MOTOR_DIRECTION);
	
	//Srkur på motoren
	set_bit(MOTORBOX_CONTROLL_REG, MOTOR_ENABLE);
	
	//Enabler output, velger lowbit, setter direction til -1
	MOTORBOX_CONTROLL_REG &= ~((1<<ENCODER_OUTPUTENABLE_NOT)|(1<<ENCODER_SELECTHIGHBIT)|(1<<MOTOR_DIRECTION));
	motorbox_reset_encoder();
}


void motorbox_set_percent(int16_t percent){
	if(percent > 100){
		percent = 100;
	}
	else if(percent < -100){
		percent = -100;
	}
	if(percent<MOTOR_SLACK_TURNOFF && percent>-MOTOR_SLACK_TURNOFF){
		motorbox_set_power(!POS_DIR, 0);
	}
	else if(percent < 0){
		motorbox_set_power(!POS_DIR, -percent +MOTOR_SLACK_OFFSET);
	}
	else{
		motorbox_set_power(POS_DIR, percent +MOTOR_SLACK_OFFSET);
	}
}

void motorbox_set_power(uint8_t dir, uint8_t power){
	if(dir){
		set_bit(MOTORBOX_CONTROLL_REG,MOTOR_DIRECTION);
	}
	else{
		clear_bit(MOTORBOX_CONTROLL_REG,MOTOR_DIRECTION);
	}
	I2C_transmit(power,DAC_ADRESS);	
}

int16_t motorbox_get_encoder(){
	set_bit(MOTORBOX_CONTROLL_REG,ENCODER_SELECTHIGHBIT);
	_delay_us(20);
	uint16_t encoder_data = reverse_byte(MOTORBOX_DATA_PIN);;
	clear_bit(MOTORBOX_CONTROLL_REG,ENCODER_SELECTHIGHBIT);
	_delay_us(20);
	encoder_data |= (reverse_byte(MOTORBOX_DATA_PIN)<<8); //The encoder data is inverted, so we have to deinvert
	return -BOARD_SIZE/2-encoder_data;	//The motor is going to start in the left corner, we want the middle of the board to be 0
}

void motorbox_reset_encoder(){
	clear_bit(MOTORBOX_CONTROLL_REG,ENCODER_RESET_NOT);
	_delay_us(20);
	set_bit(MOTORBOX_CONTROLL_REG,ENCODER_RESET_NOT);
}

uint8_t reverse_byte(uint8_t b) {
	b = (b & 0b11110000) >> 4 | (b & 0b00001111) << 4; //Swaps the 4msb and 4lsb
	b = (b & 0b11001100) >> 2 | (b & 0b00110011) << 2; //Of the 4msb, the 2msb and 2lsb are swapped, same with the 4lsb
	b = (b & 0b10101010) >> 1 | (b & 0b01010101) << 1; //Of the 2msb the msb and lsb are swapped, same with all the other pairs
	return b;
}