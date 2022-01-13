#include <avr/io.h>
#include <avr/delay.h>

/* static int rapport = 0; */

void TIMER0_COMPA_vect (void) __attribute__ ((signal,__INTR_ATTRS));

void TIMER0_COMPA_vect (void) {
	/* if (OCR0A % 40) */
		PORTB ^= (1 << PORTB3);
	/* OCR0A++; */
	/* if (rapport < 100) */
	/* 	rapport--; */
	/* else */
	/* 	rapport++; */
}

void duty_cycle() {
	DDRB |= (1 << DDB1);
	TCCR1B = (1 << CS12) | (1 << CS10);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);

	TCCR1A = (1 << WGM11);
	TCCR1A |= (1 << COM1A1);
	ICR1 = 15624; // F_CPU / 1024 / 2
}

void init () {
	OCR0A= 1000;
	DDRB |= (1 << DDB3);

	TCNT0 = 0; //initialize counter value to 0
	TCCR0A = (1 << WGM01); //turn on CTC mode
	TCCR0B = (0 << CS02) | (0 << CS01) | (1 << CS00);
	
	TIMSK0 = (1 << OCIE0A);

	/* /1* Clear overflow flag *1/ */
	TIFR0  = 1<<TOV1;

	/* enable global interupt */
	SREG = (1 << 7);
}

int main() {
	/* duty_cycle(); */
	init();
	while (1) {
		/* OCR0A++; */
		/* OCR1A = ICR1 / rapport; */
		/* OCR1A = ICR1 * rapport / 100; */
	}
	return 1;
}
