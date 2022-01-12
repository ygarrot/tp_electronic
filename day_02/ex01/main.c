#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t counter = 0; // this counts the number of timer overflows

/* • Vous devez configurer les registres du Timer1 pour commander la LED. */
ISR (TIMER1_COMPA_vect) {
	counter++;
	PORTB ^= 1 << PORTB1;
	if (counter >= 1000){
		PORTB ^= 1 << PORTB3;
		counter = 0;
	}
}

void init_timer() {
	OCR1A = 7812; 
	/* Timer/Counter Control Register */
	/* • Bit 3 – WGM[x]2: Waveform Generation Mode */

	/* TCCR1A = (1 << WGM12); */
	/* Bits 2:0 – CS02:0: Clock Select */
	/* CS12 */
	TCCR1B = (1 << CS12) | (1 << CS10);
	/* TIMSK = Timer Interrupt Mask Register */
	TIMSK1 = (1 << OCIE1A);
	/* sei(); */
}

int main() {
	DDRB |= (1 << DDB1);
	init_timer();
	while (1){
	}
	return 0;
}
