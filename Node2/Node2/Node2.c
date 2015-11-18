#include "CommunicationDrivers/can.h"
#include "MainInclude.h"
#include "CommunicationDrivers/UsartDriver.h"
#include "MotorDrivers/servo.h"
#include "InternalDrivers/adc.h"
#include "CommunicationDrivers/I2C.h"
#include "regulator.h"
#include "MotorDrivers/Solenoid.h"
#include "SensorDrivers/HC-SR04.h"

#include <avr/interrupt.h>

int main(){
	sei(); // Global interrupt enable
	//cli(); // Global interrupt disable
	
	/*INITIALISATION*/
	USART_init();
	puts("Uart init done");
	CAN_init();
	puts("Can init done");
	servo_init();
	puts("Servo init done");
	adc_init();
	puts("ADC init done");
	I2C_init();
	puts("I2C init done");
	motorbox_init();
	puts("Motor init done");
	HCSR04_inti();
	puts("Distance sensor init done");
	SOLENOID_DDR |= 1<<SOLENOID_BIT;
	set_bit(SOLENOID_PORT,SOLENOID_BIT);
	
	/*Tillstandsvariable*/
	interrupt CAN_interrupt;
	uint8_t new_msg;
	
	CAN_message msgInn0;
	msgInn0.length = 0;
	
	CAN_message msgGameSignal;
	msgPoint.length = GAMESIGNAL_MSGLEN;
	msgPoint.id = NODE1_CANID_0;
	msgPoint.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_GAMESIGNAL;
	
	ADC_signal adcSignal;
	Regulator regulator;
	regulator_init(&regulator);
	puts("Regulator init done");
	
	//BURDE KJØØRE HCSR04_init(&S0_data) sånn som regulator_init
	HCSR04_data S0_data;
	HCSR04_data S1_data;
	S0_data.queuePointer = 0;
	S1_data.queuePointer = 0;
	S0_data.pos_ref = 0;
	S1_data.pos_ref = 0;
	for(uint8_t i=0;i<HCSR04_averagingPeriod;++i){
		S0_data.mesurements[i] = 0;
		S1_data.mesurements[i] = 0;
	}
	S0_data.sum = 0;
	S1_data.sum = 0;
	
	
	int16_t joySpeed = 0;
	int16_t joyPos = 0;
	
	
	uint8_t gameMode = GAMEMODE_OFF;
	uint8_t gameModeChanged = 0;
	
	uint8_t push = 0;
	
	puts("All init done");
	while(1){
		CAN_interrupt = CAN_int();
		switch(CAN_interrupt){
			case NOINT:
				break;
			case ERR:
				printf("CAN ERROR");
				break;
			case RX0:
				CAN_data_receive(&msgInn0, MCP_RXB0CTRL);
				break;
			case RX1:
				CAN_data_receive(&msgInn0, MCP_RXB1CTRL);
				break;
			default:
				break;
		}
		//Resets the interrupt if there was one
		if(CAN_interrupt != NOINT) CAN_int_clear(CAN_interrupt);
		//if we got a message, then the length would be non 0
		if(msgInn0.length){
			switch(msgInn0.data[CANMSG_PACKAGESPECIFIER]){
				case PACKAGESPECIFIER_MOTORSIGNALS:
					msgInn0.length = 0; //Indicates that the message is read
				break;
				case PACKAGESPECIFIER_GAMEMODE:
					gameMode = msgInn0.data[GAMEMODE_MODE_BYTE];
					gameModeChanged = 1;
					msgInn0.length = 0; //Indicates that the message is read
				break;
			}
			
		}
		
		
		if(gameMode != GAMEMODE_OFF){
			//if the gamemode changed to this state, then things need to be activated
			if(gameModeChanged){
				REGULATOR_TIMER_ACTIVATE;
			}
			
						
			//Measures if the led i blocked
			adc_measure(&adcSignal);
			
			//Writes down the time interval since last round.
			//Used in the regulator, and other integral action
			regulator.dt = TCNT3*1.0/((F_CPU/64)*1.0);
			TCNT3 = 0;	//Resets the timer.
			
			//Sets the servo accorging to the slider from node1
			servo_set(msgInn0.data[CANMSG_SLIDERR_BYTE]);
			
			if(gameMode == GAMEMODE_JS){
				//The joystick indicates the movement speed of the motor
				joySpeed = msgInn0.data[CANMSG_JSX_BYTE];
				//We integrate up the joystick signal to get a position reference. 
				joyPos += get_pos_from_percent(joySpeed)* regulator.dt * CONTROLLER_GAIN;
				//Runs the regulator with the integrated joystick signal as position reference.
				regulator_increment(&regulator,joyPos);
				
				//If button R is pressed, then the sollenoid is supposed to push.
				push = msgInn0.data[CANMSG_BTNR_BYTE] & (1<<CANMSG_BTNR_BIT);
			}
			
			else if(gameMode == GAMEMODE_SENS){
				//The echo sensor indicates the motor possition.
				HCSR04_update_ref(&S0_data,SENSOR0, ISC20);
				//Echo sensor 1 is used to activated the solenoid
				HCSR04_update_ref(&S1_data,SENSOR1, ISC30);
				//Runs the regulator with echo sensor possition reference.
				regulator_increment(&regulator, S0_data.pos_ref);
				
				//Echo sensor 1 will measure the distance to the other side of the box most of the time
				//If it measures a suffitently lower value, then the player is blocing it
				if(S1_data.pos_ref < BOARD_SIZE/2 - S1_ACTIVATION_DISTANCE){
					push = 1;
				}
				else push = 0;
				
			}
			
			//Set the motorpower acording to the regulator.
			motorbox_set_percent(regulator.u);
			
			//Activates or deactivates the solenoid
			//If the solenoid was previously deactive and we want to activate it
			if(push && read_bit(SOLENOID_PORT,SOLENOID_BIT)){				
				//Activates
				clear_bit(SOLENOID_PORT,SOLENOID_BIT);
				//Sends a signal indicating that the player pushed the solenoid
				//This is going to start the game, if it has not allready started.
				msgGameSignal.data[GAMESIGNAL_SIGNAL_BYTE] = GAMESIGNAL_START;
				CAN_message_send(&msgPoint);
			}
			//If the solenoid was previusly active and we want to deactivate it
			else if(!push && !read_bit(SOLENOID_PORT,SOLENOID_BIT)){
				set_bit(SOLENOID_PORT,SOLENOID_BIT);
			}
			
			//if there was a rising edge on the adcSignal, then the game is lost
			if(adcSignal.edge){
				msgGameSignal.data[GAMESIGNAL_SIGNAL_BYTE] = GAMESIGNAL_STOP;
				CAN_message_send(&msgPoint);
			}
		}
		else{
			REGULATOR_TIMER_DEACTIVATE;
			//Stops the motor
			motorbox_set_percent(0);
			//Resets the encoder. (Burde skje ved gamestart)
			motorbox_reset_encoder();
			set_bit(SOLENOID_PORT,SOLENOID_BIT); //retract solenoid
		}		
	}
	return 0;
}