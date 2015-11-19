/*
 * I2C.c
 *
 * Created: 30.10.2015 09:55:57
 *  Author: sverrevr
*/ 

#include "../MainInclude.h"
#include "I2C.h"
#include "I2C_defines.h"

//I2C clock max 400 kHz
//I2c klokken = cpuclock / (16+2*bitrateregister * prescaler); //prescaler = 4^bitveriden
//Velger clock lik 285 714Hz ved prescaler lik 4^1 = 4, bitrate register = 5.

void I2C_init(){
	//Finn utgangen, og sett den til output?
	//I2C klokkehastighet på 285 714hz
	TWBR = 5;		//bitrate register
	TWSR |= (0b01); //Prescaler, 2 bit, gir scaling på 4^bitverdi
	//set_bit(TWCR,TWEA); //Enable acknowledge bit //Muilig vi må gjøre det hver gang vi skal sende
	
	TWAR = (0b0001000 << 1) | (1 << 0); //Node2 sin adresse er 0000001, siste 1bit er at vi hører på general calls
	/*TWAMR disables bitene i adresse. Tror ikke vi trenger det?*/
	
	//red_bit(TWCR, TWWC); //Write collision flag, ?
	set_bit(TWCR,TWEN); //Aktiverer I2C
	//set_bit(TWCR,TWIE); //Interupt enable. Tror dette er ordentlig interupts, så det driter vi i.
	//uint8_t I2C_status = (TWSR >> 3);
	//TWDR = 0xff; //1 byte. I transmit mode: dataen som skal sendes. I receve mode: Dataen den har fått inn
	TWDR = 0xFF;
}

void I2C_transmit(uint8_t data, uint8_t addr){
	TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN); //Sender startbit, interupt clear og enable for å sende siganl
	while(!I2C_getInterrupt());	//Venter til start signalet er sendt
	//printf("State:%u\n",TWSR&0xF8); //Start transmitted. BRA!

	TWDR = (addr<<1) | 0b0; //Sender adressen inn i transmittbuffer. Siste 7 er adresse, 1 bit er R/!W.
	TWCR = (1<<TWINT)|(1<<TWEN); //Interupt clear og enable for å sende
	
	while(!I2C_getInterrupt());	//Interupt når slave addr + write er sendt, og ack er motatt
	
	//printf("State:%u\n",TWSR&0xF8); //SLA+w has been transmited. Bra!
	
	/*000 må være 0. RST 1 for reset alle DAC registere. PD 1->shut down mode (0 -> vanlig). A2(ignored) A1 A0 velger dac fra 0 til 3*/
	TWDR = 0b00000000; //Bruk dac0, ikke reset eller power down.
	TWCR = (1<<TWINT)|(1<<TWEN); //Interupt clear og enable for å sende
	
	while(!I2C_getInterrupt());	//Interupt når controll signal er sendt, og ack er motatt
	
	//printf("State:%u\n",TWSR&0xF8); //Data sendt, bra!
	
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN); //Interupt clear og enable for å sende
	
	while(!I2C_getInterrupt());	//Interupt når data er sendt, og ack er motatt
	
	//printf("State:%u\n\n",TWSR&0xF8); //Data sendt, bra!
	
	TWCR = (1<<TWSTO)|(1<<TWINT)|(1<<TWEN); //Stopbit, Interupt clear og enable for å sende
}

//Forteller at den er ferdig med oppgaven
uint8_t I2C_getInterrupt(){
	return read_bit(TWCR,TWINT);
}
//Setter flagget lavt som får den til å begynne med en oppgave
void I2C_clearInterupt(){
	set_bit(TWCR,TWINT);
}

uint8_t test_state(uint8_t state){
	return (TWSR&0xF8) == state;
}