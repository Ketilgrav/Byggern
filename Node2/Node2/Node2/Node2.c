#include "CommunicationDrivers/can.h"
#include "MainInclude/MainInclude.h"
#include "CommunicationDrivers/UsartDriver.h"
#include "MotorDrivers/servo.h"

int main(){
	USART_init();
	CAN_init();
	servo_init();
	interrupt CAN_interrupt;
	
	CAN_message msgInn0;
	
	while(1){
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
				printf("X: %i    \t", msgInn0.data[0]);
				printf("Y: %i    \r", msgInn0.data[1]);
				break;
			case RX1:
				//printf("Receved on RX1\n");
				CAN_data_receive(&msgInn0, MCP_RXB1CTRL);
				printf("X: %i    \t", msgInn0.data[0]);
				printf("Y: %i    \r", msgInn0.data[1]);
				break;
			default:
				break;
		}
		CAN_int_clear(CAN_interrupt);
		
		servo_set(msgInn0.data[0]);
	}
	return 0;
}