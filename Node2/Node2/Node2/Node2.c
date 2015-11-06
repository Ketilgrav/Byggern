#include "CommunicationDrivers/can.h"
#include "MainInclude/MainInclude.h"
#include "CommunicationDrivers/UsartDriver.h"
#include "MotorDrivers/servo.h"
#include "InternalDrivers/adc.h"
#include "CommunicationDrivers/I2C.h"
#include "../../../InterNodeHeaders/CanMessageFormat.h"
#include "regulator.h"

int main(){
	USART_init();
	CAN_init();
	servo_init();
	adc_init();
	I2C_init();
	motorbox_init();
	interrupt CAN_interrupt;
	
	CAN_message msgInn0;
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
				break;
			case RX1:
				//printf("Receved on RX1\n");
				CAN_data_receive(&msgInn0, MCP_RXB1CTRL);
				break;
			default:
				break;
		}
		CAN_int_clear(CAN_interrupt);
		switch(msgInn0.data[CANMSG_PACKAGESPECIFIER]){
			case PACKAGESPECIFIER_MOTORSIGNALS:
				servo_set(msgInn0.data[CANMSG_SERVO]);
				reg_ref = msgInn0.data[CANMSG_MOTOR];
			break;
			case PACKAGESPECIFIER_SWITCHOFF:
				//printf("SWITCHING OFFF");
				servo_set(0);
				motorbox_set_percent(0);
			break;
		}
		adc_measure(&adcSignal);
		
		regulator_increment(&pi_state,reg_ref);
		motorbox_set_percent(pi_state.u);
		printf("U:%i    ", (get_pos_from_percent(reg_ref)-motorbox_get_encoder())/(board_size/100));
		printf("Encoder:%i    \r", motorbox_get_encoder());
		
		//printf("Encoder diff: %i       \r",motorbox_get_encoder());
		//motorbox_reset_encoder();
		//printf("%u",reverse_byte(0));
		
		
	}
	return 0;
}