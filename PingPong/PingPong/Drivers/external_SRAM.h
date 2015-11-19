/*
 * external_SRAM.h
 *
 * Created: 04.09.2015 13:14:58
 *  Author: sverrevr
 */ 
#include "../MainInclude.h"


#ifndef EXTERNAL_SRAM_H_
#define EXTERNAL_SRAM_H_

#define RAM_START_ADR 0x1800
#define EXT_RAM_SIZE 0x800 //2048 = 2^11. We have 11 address lines, so we can access 2048 memory locations.

void SRAM_init(void);
void SRAM_test(void);




#endif /* EXTERNAL_SRAM_H_ */
