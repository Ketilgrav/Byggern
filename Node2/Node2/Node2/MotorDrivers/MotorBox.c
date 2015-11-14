/*
 * MotorBOx.c
 *
 * Created: 06.11.2015 08:35:33
 *  Author: sverrevr
 */ 

#include "MotorBox.h"

void motorbox_init(){
	MOTORBOX_CONTROLL_DDR |= (1<<ENCODER_OUTPUTENABLE_NOT)|(1<<ENCODER_RESET_NOT)|(1<<ENCODER_SELECTHIGHBIT)|(1<<MOTOR_ENABLE)|(1<<MOTOR_DIRECTION);
	clear_bit(MOTORBOX_CONTROLL_REG,ENCODER_RESET_NOT);
	//Velger å ikke resette, skrur på motor
	MOTORBOX_CONTROLL_REG |= (1<<ENCODER_RESET_NOT)|(1<<MOTOR_ENABLE);
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
	if(percent<10 && percent>-10){
		motorbox_set_power(!POS_DIR, 0);
	}
	else if(percent < 0){
		motorbox_set_power(!POS_DIR, -percent + 35);
	}
	else{
		motorbox_set_power(POS_DIR, percent +35);
	}
}

void motorbox_set_power(uint8_t dir, uint8_t power){
	if(dir){
		set_bit(MOTORBOX_CONTROLL_REG,MOTOR_DIRECTION);
	}
	else{
		clear_bit(MOTORBOX_CONTROLL_REG,MOTOR_DIRECTION);
	}
	//printf("%u \r",power);
	I2C_transmit(power,DAC_ADRESS);	
}

int16_t motorbox_get_encoder(){
	set_bit(MOTORBOX_CONTROLL_REG,ENCODER_SELECTHIGHBIT);
	_delay_us(20);
	uint16_t encoder_data = reverse_byte(MOTORBOX_DATA_PIN);;
	clear_bit(MOTORBOX_CONTROLL_REG,ENCODER_SELECTHIGHBIT);
	_delay_us(20);
	encoder_data |= (reverse_byte(MOTORBOX_DATA_PIN)<<8);
	return -board_size/2-encoder_data;
}

void motorbox_reset_encoder(){
	clear_bit(MOTORBOX_CONTROLL_REG,ENCODER_RESET_NOT);
	_delay_us(20);
	set_bit(MOTORBOX_CONTROLL_REG,ENCODER_RESET_NOT);
}

uint8_t reverse_byte(uint8_t b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}