#include <avr/io.h>
#include <avr/delay.h>

int main() {
	/* on indique que le bit 1 du port b est en output */
	DDRB |= (1 << DDB3);
	/* on indique que le bit 3 du port d est en input */
	DDRC &= ~(1 << PORTD3);

	/* 0 | 1 Any logical change on INT0 generates an interrupt request. */
	EICRA = 1 << ISC11;

	/* enable global interupt */
	SREG = (1 << 7);

	while (1) {
		if (EIFR & (1 << INTF1)) {
			PORTB ^= (1 << PORTB3);
			EIFR = (1 << INTF1);
			_delay_ms(250);
		}
	}
	return 1;
}
