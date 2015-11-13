#include "CommunicationDrivers/can.h"
#include "MainInclude/MainInclude.h"
#include "CommunicationDrivers/UsartDriver.h"
#include "MotorDrivers/servo.h"
#include "InternalDrivers/adc.h"
#include "CommunicationDrivers/I2C.h"
#include "../../../InterNodeHeaders/CanMessageFormat.h"
#include "regulator.h"
#include "MotorDrivers/Solenoid.h"

int main(){
	USART_init();
	CAN_init();
	servo_init();
	adc_init();
	I2C_init();
	motorbox_init();
	SOLENOID_DDR |= 1<<SOLENOID_BIT;
	interrupt CAN_interrupt;
	
	CAN_message msgInn0;
	uint8_t new_msg;
	ADC_signal adcSignal;
	PI pi_state;
	int8_t reg_ref;
	regulator_init(&pi_state);
	while(1){
		uint16_t encoder = motorbox_get_encoder();
		CAN_interrupt = CAN_int();
		switch(CAN_interrupt){
			case NOINT:
				//printf("No intrpt\n");
				break;
			case ERR:
				//printf("Error\n");
				break;
			case RX0:
				//printf("Receved on RX0\n");
				CAN_data_receive(&msgInn0, MCP_RXB0CTRL);
				new_msg = 1;
				break;
			case RX1:
				//printf("Receved on RX1\n");
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
				reg_ref = msgInn0.data[CANMSG_MOTOR];
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
				reg_ref = 0;
				break;
			}	
		}
		new_msg = 0;
		adc_measure(&adcSignal);
		
		regulator_increment(&pi_state,reg_ref);
		motorbox_set_percent(pi_state.u);
	}
	return 0;
}