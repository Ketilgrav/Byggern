/*
 * CFile1.c
 *
 * Created: 10.11.2015 09:39:48
 *  Author: sverrevr
 */ 

/*
DEafult controll pipe er 0. Litt tipping siden nr 1 har 256bytes, og ikke nr 0
*/




/*
USB power on:
Power on Pads regulator
Configure PLL interface
Enable PLL and wait PLL lock
Enable USB interface
COnfigure USB interface
Wait for USB VBUS information connection
Attach USB device

USB power off:
Detach USB interface
Disable USB interface
Disable PLL
Disable USB pad regulator
*/
#include "USB.h"

void USB_init_general(){
	USBCON |= (1<<USBE); //Enable USB. 0 - disable og reset
	
	//Må cleare detach før jeg går inn i host mode:
	clear_bit(UDCON,DETACH);
	
	USBCON |= (1<<HOST); //Enable host mode
	clear_bit(USBCON, FRZCLK); //Unfreezer klokka.
	USBCON |= (1<<OTGPADE); //Wnable OTG pad som egentlig er VBUS pad.
	USBCON |= (1<<IDTE); //ID transition interupt generation
	USBCON |= (1<<VBUSTE); //Vbus transition interupt generation
	
	clear_bit(UHWCON,UIMOD);	//Host mode,
	clear_bit(UHWCON,UIDE);		//bruke register for å bestemme mode, istedet for UID som ikke er koblet til noe
	set_bit(UHWCON, UVCONE);	//The Host must use the UVCON pin to drive an external power switch or regulator that powers the Vbus line. The UVCON pin is automatically asserted and set high by hardware when UVCONE and VBUSREQ bits are set by firmware
	set_bit(UHWCON, UVREGE);	//aktiverer pad regulator (trengs for å kjøre Usb)
		
	

	//Kan lese:
	//(USBSTA & SPEED) 1=full speed mode, 0=low speed mode
	//(USBSTA & ID) Statusen på UID pin
	//(USBSTA & VBUS) Staten til VBUS, brukes bare i device mode?
	
	//Interuptene vi kunne enable over:
	//(USBINT & IDTI) og (USBINT & VBUSTI) må cleares av software.
	
	OTGCON |= (1<<HNPREQ);	//1: aksepterer HNP
	clear_bit(OTGCON, SRPSEL);	//1: VBUS pulsing as SRP method, 0: data line pulsing as SRP. Kan ikke pulse VBUS, så slik.
	OTGCON |= (1<<VBUSHWC); //Set to disable hardware controll over UVCON pin
	
	//UVCON assert og deassert. Må gjøres av host
	//Asert og deassert fører til enable VBUS power supply generation??
	OTGCON |= (1<<VBUSREQ); //Cleares når neste kjøres (clear)
	OTGCON |= (1<<VBUSRQC); //Cleares immediatly
	
	//Kan ha spesielle timer ting nederst side 259
	
	//OTGIEN: Interupt enable for: suspend Time-out, HNP error, Role exchange, BCERRE b connect error, vbus error, srp interrupt
	//OTGINT: Lese interuptene:
}



void USB_init(){	
	USB_init_general();
	
	//HC = Hardware cleared
	//Host stuff:
	//Må disable DETACH først
	
	UHCON |= (0<<RESUME);	//Sender resume signal. Kun ved SOFEN = 1. HC
	UHCON |= (0<<RESET);	//Sender USB reset signal. HC
	UHCON |= (1<<SOFEN);	//Generer SOF på busen i fullspeed, keep-alive i low speed. 0-idle usb bus
	
	//TOp 293 for interupts. Host wakeup, Host start of frame, upstream resume, downstream resume, usb reset sent, device disconnection, device connection
	 
	//USB host adress
	UHADDR = 0x99; //Hva skal vi velge?
	//Frame number: ligger i de 11 første bitene på UHFNUM, kan endres
	//UHFLEN data frame length transmited
	
	
	//Herfra pipe nr 0
	UPNUM |= 0b000; //Slect pipe number 0
	//uprst sende reset til en pipe, pipe 0 er bit 0, pipe 6 er bit 6
	
	UPCONX &= ~(1<<PFREEZE); //Clear to unfreez, Freezes ved feil. Kan også freeze ved å sette til 1
	
	UPCONX |= (1<<INMODE);	//Lar den sende infinite IN requests Om vi ikke har inf se UPINRQX
	UPCONX |= (0<<RSTDT);	//Reset data toggle til init verdi. HC
	UPCONX |= (1<<PEN);		//Pipe enable
	
	
	//Velger pipe type
	UPCFG0X |= (1<<PTYPE1)|(1<<PTYPE0); //Interrupt type pipe. Passer for keyboard mouse
	UPCFG0X |= (0<<PTOKEN1)|(1<<PTOKEN0); //01 IN, 10 OUT , 00 SETUP. Skal hvertfall ha IN til vanelig
	UPCFG0X |= 0b001 << PEPNUM0; //Antall endpoints i pipen, skal settes according til pipe configuration
	
	UPCFG1X |= (0b000 << PSIZE0); //Fra 000 til 101 gir pipe size 8 - 256 (2gang oppover)
	UPCFG1X |= (0<<PBK0); //0: 1bank, 1: 2 bank
	
	UPCFG1X |= (1<<ALLOC); /*Set to configure the pipe memory with the characteristics.
	Clear to update the memory allocation. Refer to the Memory Management chapter for more
	details	*/
	
	UPCFG2X = 0xFF; //MAx tid i ms for polling period for en interrupt pipe
	
	//(UPSTAX & 1<<CFGOK) required memory config var successfull
	//(UPSTAX & 1<<OVERFI) om vi har fått mer data enn max størrelsen av pipen
	//(UPSTAX & 1<<UNDERFI) ???
	///UPSTAX & 1<<DTSEQ0) //Indicate PID data of the current bank
	//(UPSTAX & 0b11 << NBUSYBK0)//00 2 bankns free, 01, 1 free, 10 0 free
	
	//Error counter, teller opp til 3 da freezes pipen, cleares av software
	//(UPERRX & 1<<COUNTER) 
	//Har også error flag for: CRC16n error,Timeout error, PID error, DATAPID error, bad data
	
	//UPINTX interputs, UPIENX enable
	//RXIN er om vi ha fåt data, denne er viktig, se diagram på in ting.
	
	//UPDATX = 0xFF; //Set/les byte fra/til pipe FIFO selected by PNUM
	//UPBCX; Byte count: Out: increase ved hver writing til pipe, decrement  after each byte sent.
	//IN: Increase ved hver receivec, decrement ved hver lest av software.
	//Så da er UPDATAX en byte, vi leser den, og da sendes inn en ny. UPBCX er antall bytes som venter?
	//UPINT pipe interupt	
}



uint8_t USB_read(){
	
}