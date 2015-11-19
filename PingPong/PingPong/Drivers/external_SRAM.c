/*
 * external_SRAM.c
 *
 * Created: 04.09.2015 13:14:46
 *  Author: sverrevr
 */ 

#include "external_SRAM.h"

void SRAM_init(void){
	set_bit(MCUCR, SRE);	//External ram enable
	set_bit(SFIOR, XMM2);	//100 -> release pc7-pc4 from memory operations, for use in jtag.
	SRAM_test();
}

void SRAM_test(void){
	volatile char *ext_ram = (char *) RAM_START_ADR; 
	uint16_t ext_ram_size = EXT_RAM_SIZE; 
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n\r");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;			//Set a random value
		uint8_t retreived_value = ext_ram[i];		//Retrieve said value
		if (retreived_value != some_value) {		//Compare set and retrieved
			//printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i,retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase 
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			//printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n\r%4d errors in write phase and \n\r%4d errors in retrieval phase \n \n\r", write_errors, retrieval_errors);
}
