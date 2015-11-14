#include "CommunicationDrivers/can.h"
#include "MainInclude.h"
#include "CommunicationDrivers/UsartDriver.h"
#include "MotorDrivers/servo.h"
#include "InternalDrivers/adc.h"
#include "CommunicationDrivers/I2C.h"
#include "../../../InterNodeHeaders/CanMessageFormat.h"
#include "regulator.h"
#include "MotorDrivers/Solenoid.h"
#include "SensorDrivers/HC-SR04.h"

int main(){
	/*INITIALISATION*/
	USART_init();
	CAN_init();
	servo_init();
	adc_init();
	I2C_init();
	motorbox_init();
	SOLENOID_DDR |= 1<<SOLENOID_BIT;
	
	/*Tillstandsvariable*/
	interrupt CAN_interrupt;
	uint8_t new_msg;
	CAN_message msgInn0;
	ADC_signal adcSignal;
	PI pi_state;
	int8_t pos_ref;
	uint16_t encoder;
	regulator_init(&pi_state);
	
	while(1){
		printf("%u   \r",HCSR04_measure());
		encoder = motorbox_get_encoder();
		CAN_interrupt = CAN_int();
		switch(CAN_interrupt){
			case NOINT:
				break;
			case ERR:
				printf("CAN ERROR");
				break;
			case RX0:
				CAN_data_receive(&msgInn0, MCP_RXB0CTRL);
				new_msg = 1;
				break;
			case RX1:
				CAN_data_receive(&msgInn0, MCP_RXB1CTRL);
				new_msg = 1;
				break;
			default:
				break;
		}
		CAN_int_clear(CAN_interrupt);
		if(new_msg){
			switch(msgInn0.data[CANMSG_PACKAGESPECIFIER]){
				case PACKAGESPECIFIER_MOTORSIGNALS:
				servo_set(msgInn0.data[CANMSG_SERVO]);
				pos_ref = msgInn0.data[CANMSG_MOTOR];
				if(msgInn0.data[CANMSG_PUSH_BYTE]){
					set_bit(SOLENOID_PORT,SOLENOID_BIT);
				}
				else{
					//printf("Wait\r");
					clear_bit(SOLENOID_PORT,SOLENOID_BIT);
				}
				break;
				case PACKAGESPECIFIER_SWITCHOFF:
					//printf("SWITCHING OFFF");
					servo_set(0);
				break;
			}	
		}
		new_msg = 0;
		adc_measure(&adcSignal);
		
		regulator_increment(&pi_state,pos_ref);
		motorbox_set_percent(pi_state.u);
	}
	return 0;
}