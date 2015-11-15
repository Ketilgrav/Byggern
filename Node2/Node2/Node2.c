#include "CommunicationDrivers/can.h"
#include "MainInclude.h"
#include "CommunicationDrivers/UsartDriver.h"
#include "MotorDrivers/servo.h"
#include "InternalDrivers/adc.h"
#include "CommunicationDrivers/I2C.h"
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
	HCSR04_inti();
	SOLENOID_DDR |= 1<<SOLENOID_BIT;
	
	/*Tillstandsvariable*/
	interrupt CAN_interrupt;
	uint8_t new_msg;
	
	CAN_message msgInn0;
	msgInn0.length = 0;
	
	CAN_message msgPoint;
	msgPoint.length = 1;
	msgPoint.id = NODE1_CANID_0;
	msgPoint.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_GAMEPOINT;
	
	ADC_signal adcSignal;
	Regulator regulator;
	regulator_init(&regulator);
	
	//BURDE KJØØRE HCSR04_init(&S0_data) sånn som regulator_init
	HCSR04_data S0_data;
	HCSR04_data S1_data;
	S0_data.queuePointer = 0;
	S1_data.queuePointer = 0;
	for(uint8_t i=0;i<HCSR04_averagingPeriod;++i){
		S0_data.mesurements[i] = 0;
		// WTF SKJER HER????
		S0_data.mesurements[i] = 100;
	}
	
	int16_t joySpeed = 0;
	int16_t joyPos = 0;
	
	
	uint8_t gameMode = GAMEMODE_OFF;
	
	uint8_t push = 0;
	while(1){
		adc_measure(&adcSignal);
		//printf("%i   \r",dist_data.pos_ref);
		
		CAN_interrupt = CAN_int();
		switch(CAN_interrupt){
			case NOINT:
				break;
			case ERR:
				printf("CAN ERROR");
				break;
			case RX0:
				CAN_data_receive(&msgInn0, MCP_RXB0CTRL);
				//printf("RX0: %i\t%i   \t%i   \t%i   \r",msgInn0.data[CANMSG_PACKAGESPECIFIER],msgInn0.data[CANMSG_BTNR_BYTE],msgInn0.data[CANMSG_SLIDERR_BYTE],msgInn0.data[CANMSG_JSX_BYTE]);
				break;
			case RX1:
				CAN_data_receive(&msgInn0, MCP_RXB1CTRL);
				//printf("RX0: %i\t%i   \t%i   \t%i   \r",msgInn0.data[CANMSG_PACKAGESPECIFIER],msgInn0.data[CANMSG_BTNR_BYTE],msgInn0.data[CANMSG_SLIDERR_BYTE],msgInn0.data[CANMSG_JSX_BYTE]);
				break;
			default:
				break;
		}
		CAN_int_clear(CAN_interrupt);
		
		if(msgInn0.length){
			switch(msgInn0.data[CANMSG_PACKAGESPECIFIER]){
				case PACKAGESPECIFIER_MOTORSIGNALS:
					msgInn0.length = 0;
				break;
				case PACKAGESPECIFIER_GAMEMODE:
					gameMode = msgInn0.data[GAMEMODE_MODE_BYTE];
					msgInn0.length = 0;
				break;
			}
			
		}
		
		//printf("%i\r\n",msgInn0.data[CANMSG_SLIDERR_BYTE]);
		if(gameMode != GAMEMODE_OFF){
			servo_set(msgInn0.data[CANMSG_SLIDERR_BYTE]);
			regulator.dt = TCNT3*1.0/((F_CPU/64)*1.0);
			TCNT3 = 0;	
			if(gameMode == GAMEMODE_JS){
				//printf("JS  \r");
				joySpeed = msgInn0.data[CANMSG_JSX_BYTE];
				joyPos += get_pos_from_percent(joySpeed)* regulator.dt * CONTROLLER_GAIN;
				//printf("%i\r",joyPos);
				regulator_increment(&regulator,joyPos);
				push = msgInn0.data[CANMSG_BTNR_BYTE] & (1<<CANMSG_BTNR_BIT);
			}
			else if(gameMode == GAMEMODE_SENS){
				//printf("SENS  \r");
				//printf("Yo");
				HCSR04_update_ref(&S0_data,SENSOR0);
				//HCSR04_update_ref(&S1_data,SENSOR1);
				//printf("%i\r",S0_data.pos_ref);
				regulator_increment(&regulator,S0_data.pos_ref);
				if(S1_data.time < S1_ACTIVATION_POINT){
					push = 0;
				}
				else push = 0;
			}
			motorbox_set_percent(regulator.u);
			
			if(push){
				clear_bit(SOLENOID_PORT,SOLENOID_BIT);
				_delay_ms(100);
			}
			else{
				set_bit(SOLENOID_PORT,SOLENOID_BIT);
			}
		}
		else{
			printf("OFF  \r");
			TCNT3 = 0;
			motorbox_set_percent(0);
			motorbox_reset_encoder();
		}
		
		//Retursignal
		if(adcSignal.edge){
			CAN_message_send(&msgPoint);
		}
		
	}
	return 0;
}