/*
 * Solenoid.h
 *
 * Created: 13.11.2015 10:57:31
 *  Author: sverrevr
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_


#define SOLENOID_DDR DDRF
#define SOLENOID_PORT PORTF
#define SOLENOID_BIT PF2

#define SOLENOID_INIT set_bit(SOLENOID_DDR, SOLENOID_BIT)
#define SOLENOID_ACTIVATE clear_bit(SOLENOID_PORT,SOLENOID_BIT)
#define SOLENOID_DEACTIVATE set_bit(SOLENOID_PORT,SOLENOID_BIT)

#endif /* SOLENOID_H_ */