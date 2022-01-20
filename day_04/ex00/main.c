#include "tools.h"
#include "time.h"
#include <avr/eeprom.h>

#define ADDR (uint8_t*)0x00

volatile uint8_t power = 0x00;

MY_ISR(INT1_vect) {
	if (millis <= 200)
		return;
	millis = 0;

	power = (power + 1) % 18;
	eeprom_write_byte(ADDR, power);
	PORTB = power;
}

int main() {
	B_OUTPUT_FULL;
	D3_INPUT;

	enable_tick_counter();
	GLOBAL_INTERRUPT;
	EICRA = 1 << ISC11;

	PORTB = 0;
	EIMSK = 1 << INT1;
	power = eeprom_read_byte(ADDR);
	PORTB = power;
	while(1);
}

