

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void){
	DDRB = 0xff;
	while(1){
		PORTB = 0xff;
		_delay_ms(500);
		PORTB = 0;
		_delay_ms(500);
	}
}