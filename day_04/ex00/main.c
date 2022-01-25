#include "tools.h"
#include "time.h"
#include <avr/eeprom.h>

#define ADDR (uint8_t*)0x00

volatile uint8_t power = 0x00;

MY_ISR(INT0_vect) {
	if (ms_counter <= 200)
		return;
	ms_counter = 0;

	power = (power + 1) % 16;
	eeprom_write_byte(ADDR, power);
	PORTB = power;
}

int main() {
	B_OUTPUT_FULL;
	D3_INPUT;

	enable_tick_counter();
	GLOBAL_INTERRUPT;

	EICRA = 1 << ISC01;
	EIMSK = 1 << INT0;

	power = eeprom_read_byte(ADDR);
	PORTB = power;
	while(1);
}

