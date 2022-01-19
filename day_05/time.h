#ifndef __TIME_H__
#define __TIME_H__

uint64_t millis;

void delay_ms(uint64_t ms) {
	uint64_t start_millis = millis;
	while (millis - start_millis <= ms);
}

void enable_tick_counter() {
	TCCR0A = 1 << WGM01; // Set CTC mode 2
	TCCR0B |= (1 << CS01) | (1 << CS00); // Set 64 div clock
	TIMSK0 = (1 << OCIE0A); // Setup interrupt
	OCR0A = 250; // 1kHz 1ms
	TCNT0 = 0;

	millis = 0;
}

MY_ISR(TIMER0_COMPA_vect) {
	millis++;
}


#endif
