#include "CommunicationDrivers/can.h"
#include "MainInclude.h"
#include "CommunicationDrivers/UsartDriver.h"
#include "MotorDrivers/servo.h"
#include "SensorDrivers//adc.h"
#include "CommunicationDrivers/I2C.h"
#include "MotorDrivers/regulator.h"
#include "MotorDrivers/Solenoid.h"
#include "SensorDrivers/HC-SR04.h"

#include <avr/interrupt.h>

int main(){
	_delay_us(10);
	sei(); // Global interrupt enable
	//cli(); // Global interrupt disable
	
	/*INITIALISATION*/
	USART_init();
	puts("Usart init done");
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
	SOLENOID_INIT;
	SOLENOID_DEACTIVATE;
	puts("Solenoid init done");
	
	Regulator regulator;
	regulator_init(&regulator);
	puts("Regulator init done");
	
	echo_init();
	ECHO_data S0_data;
	ECHO_data S1_data;
	echo_data_init(&S0_data);
	echo_data_init(&S1_data);
	puts("Distance sensor init done");
	
	/*Tillstandsvariable*/
	/*CAN message variables*/
	interrupt CAN_interrupt;
	
	//Message holding the recieved message.
	CAN_message msgInn;
	msgInn.length = 0;
	
	//Holds a blueprint for gamesignal messages
	//msgPoint.data[GAMESIGNAL_SIGNAL_BYTE] should be updated with 
	//the correct information before sending
	CAN_message msgGameSignal;
	msgGameSignal.length = GAMESIGNAL_MSGLEN;
	msgGameSignal.id = NODE1_CANID_0;
	msgGameSignal.data[CANMSG_PACKAGESPECIFIER] = PACKAGESPECIFIER_GAMESIGNAL;
	
	
	uint8_t gameMode = GAMEMODE_OFF;
	bool gameModeChanged = false;
	
	ADC_signal adcSignal;
	
	int16_t joySpeed = 0;
	int16_t joyPos = 0;
	
	bool solenidPush = 0; //0=don't extend, 1=extend
	
	puts("All init done");
	
	while(1){
		//puts("a");
		/*Can message handeler*/
		CAN_interrupt = CAN_int();
		switch(CAN_interrupt){
			case noInt:
				break;
			case err:
				printf("CAN ERROR");
				break;
			case rx0:
				CAN_data_receive(&msgInn, MCP_RXB0CTRL);
				break;
			case rx1:
				CAN_data_receive(&msgInn, MCP_RXB1CTRL);
				break;
			default:
				break;
		}
		//Resets the interrupt
		CAN_int_clear(CAN_interrupt);
		
		//if we got a message, then the length would be non 0
		if(msgInn.length){
			switch(msgInn.data[CANMSG_PACKAGESPECIFIER]){
				case PACKAGESPECIFIER_MOTORSIGNALS:
					msgInn.length = 0; //Indicates that the message is read
				break;
				case PACKAGESPECIFIER_GAMEMODE:
					gameMode = msgInn.data[GAMEMODE_MODE_BYTE];
					gameModeChanged = 1;
					msgInn.length = 0; //Indicates that the message is read
				break;
			}
			
		}
		
		
		/*Game controll system*/
		if(gameMode != GAMEMODE_OFF){				
			//Measures if the led i blocked
			adc_measure(&adcSignal);
			
			//Writes down the time interval since last round.
			//Used in the regulator, and other integral action
			regulator.dt = TCNT3*1.0/((F_CPU/64)*1.0);
			TCNT3 = 0;	//Resets the timer.
			
			//Sets the servo accorging to the slider from node1
			servo_set(msgInn.data[CANMSG_SLIDERR_BYTE]);
			
			if(gameMode == GAMEMODE_JS){
				
				if(gameModeChanged){
					REGULATOR_TIMER_ACTIVATE;
					motorbox_reset_encoder();
					gameModeChanged = 0;
				}
				
				//The joystick indicates the movement speed of the motor
				joySpeed = msgInn.data[CANMSG_JSX_BYTE];
				//We integrate up the joystick signal to get a position reference. 
				joyPos += get_pos_from_percent(joySpeed)* regulator.dt * CONTROLLER_GAIN;
				//Runs the regulator with the integrated joystick signal as position reference.
				regulator_increment(&regulator,joyPos);
				
				//If button R is pressed, then the sollenoid is supposed to solenidPush.
				solenidPush = msgInn.data[CANMSG_BTNR_BYTE] & (1<<CANMSG_BTNR_BIT);
			}
			
			else if(gameMode == GAMEMODE_SENS){
				if(gameModeChanged){
					REGULATOR_TIMER_ACTIVATE;
					ETIMER_TRIGGER_ENABLE;
					motorbox_reset_encoder();
					gameModeChanged = 0;
				}
				
				//The echo sensor indicates the motor possition.
				echo_update_ref(&S0_data,SENSOR0, ISC20);
				//Echo sensor 1 is used to activated the solenoid
				echo_update_ref(&S1_data,SENSOR1, ISC30);
				//Runs the regulator with echo sensor possition reference.
				regulator_increment(&regulator, S0_data.pos_ref);
				
				//Echo sensor 1 will measure the distance to the other side of the box most of the time
				//If it measures a suffitently lower value, then the player is blocing it
				if(S1_data.pos_ref < BOARD_SIZE/2 - S1_ACTIVATION_DISTANCE){
					solenidPush = 1;
				}
				else solenidPush = 0;
				
			}
			
			//Set the motorpower acording to the regulator.
			motorbox_set_percent(regulator.u);
			
			//Activates or deactivates the solenoid
			//If the solenoid was previously deactive and we want to activate it
			if(solenidPush && read_bit(SOLENOID_PORT,SOLENOID_BIT)){				
				//Activates
				clear_bit(SOLENOID_PORT,SOLENOID_BIT);
				//Sends a signal indicating that the player solenidPushed the solenoid
				//This is going to start the game, if it has not allready started.
				msgGameSignal.data[GAMESIGNAL_SIGNAL_BYTE] = GAMESIGNAL_START;
				CAN_message_send(&msgGameSignal);
			}
			//If the solenoid was previusly active and we want to deactivate it
			else if(!solenidPush && !read_bit(SOLENOID_PORT,SOLENOID_BIT)){
				set_bit(SOLENOID_PORT,SOLENOID_BIT);
			}
			
			//if there was a rising edge on the adcSignal, then the game is lost
			//printf("%u",adcSignal.val);
			if(adcSignal.edge){
				msgGameSignal.data[GAMESIGNAL_SIGNAL_BYTE] = GAMESIGNAL_STOP;
				CAN_message_send(&msgGameSignal);
			}
		}
		else{
			if(gameModeChanged){
				REGULATOR_TIMER_DEACTIVATE;
				REGULATOR_TIMER_RESET;
				//turnes of the motor
				motorbox_set_percent(0);
				//retracts the solenoid
				set_bit(SOLENOID_PORT,SOLENOID_BIT); 
				gameModeChanged = 0;
				ETIMER_TRIGGER_DISABLE; 
			}
		}		
	}
	return 0;
}

ISR(BADISR_vect, ISR_NAKED){
	puts("Bad interrupt");
	asm volatile ( "ret" );
}
