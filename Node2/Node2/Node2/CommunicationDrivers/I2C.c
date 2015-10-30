/*
 * I2C.c
 *
 * Created: 30.10.2015 09:55:57
 *  Author: sverrevr
*/ 

#include "../MainInclude/MainInclude.h"

//I2C clock max 400 kHz
//I2c klokken = cpuclock / (16+2*bitrateregister * prescaler); //prescaler = 4^bitveriden
//Velger clock lik 285 714Hz ved prescaler lik 4^1 = 4, bitrate register = 5.

void I2C_init(){
	//I2C klokkehastighet p� 285 714hz
	TWBR = 5;		//bitrate register
	TWSR |= (0b01); //Prescaler, 2 bit, gir scaling p� 4^bitverdi
	set_bit(TWCR,TWEA); //Enable acknowledge bit //Muilig vi m� gj�re det hver gang vi skal sende
	
	TWAR = 0b00000011 //Node2 sin adresse er 0000001, siste 1bit er at vi h�rer p� general calls
	/*TWAMR disables bitene i adresse. Tror ikke vi trenger det?*/
	
	//red_bit(TWCR, TWWC); //Write collision flag, ?
	set_bit(TWCR,TWEN); //Aktiverer I2C
	set_bit(TWCR,TWIE); //Interupt enable. Tror dette er ordentlig interupts, s� det driter vi i.
	uint8_t I2C_status = (TWSR >> 3);
	TWDR = 0xff; //1 byte. I transmit mode: dataen som skal sendes. I receve mode: Dataen den har f�tt inn
}

void I2C_transmit(uint8_t data, uint8_t addr){
	set_bit(TWCR, TWSTA);	//Sends startbit, m� cleares
	set_bit(TWCR, TWINT);	//Clear interupt
	//TODOM� sende alle bitene sammtidit, inkludert enable!
	
	while(!I2C_getInterrupt());	//Venter til start signalet er sendt
	clear_bit(TWCR, TWSTA);		//Clearer start
	
	TWDR = (addr<<1) | 0b1; //Sender adressen inn i transmittbuffer. M� sjekke at dette er rett. Siste 7 er adresse, 1 bit er R/!W, eller er det omvendt?
	set_bit(TWCR, TWINT);	//Clear interupt. For � sende
	
	while(!I2C_getInterrupt());	//Interupt n�r slave addr + write er sendt, og ack er motatt
	
	TWDR = data;
	set_bit(TWCR, TWINT);	//Clear interupt. For � sende
	
	while(!I2C_getInterrupt());	//Interupt n�r data er sendt, og ack er motatt
	
	set_bit(TWCR, TWSTO);	//Sender stopbit, m� ikke cleares
	set_bit(TWCR, TWINT);	//Clear interupt. For � sende
	
}

//Forteller at den er ferdig med oppgaven
uint8_t I2C_getInterrupt(){
	return read_bit(TWCR,TWINT);
}
//Setter flagget lavt som f�r den til � begynne med en oppgave
uint8_t I2C_clearInterupt(){
	set_bit(TWCR,TWINT);
}

uint8_t I2C_re