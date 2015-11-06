/*
 * I2C.h
 *
 * Created: 30.10.2015 09:56:08
 *  Author: sverrevr
 */ 


#ifndef I2C_H_
#define I2C_H_

//DAC adressen:
#define DAC_ADRESS 0b0101000
void I2C_init();
void I2C_transmit(uint8_t data, uint8_t addr);
uint8_t I2C_getInterrupt();
void I2C_clearInterupt();
uint8_t test_state(uint8_t state);

#endif /* I2C_H_ */