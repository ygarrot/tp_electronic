#include <util/delay.h>
#include <avr/io.h>

void debounce () {
	while (PIND & (1 << PORTD3)) {
	}
	/* PORTB ^= 1 << PORTB3; */
	_delay_ms(1000);
	/* for (long i = 0; i < 160000000; i++); */
}

/* 1: 0 0 0 1 */
/* 2: 0 0 1 0 */
/* 3: 0 0 1 1 */
/* 4: 0 1 0 0 */
/* 5: 0 1 0 1 */
/* 6: 0 1 1 0 */
/* 7: 0 1 1 1 */

/* 8: 1 0 0 1 */

int main()
{
	int power = 0;
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);
	DDRC &= ~(1 << PORTD3);

	while (1)
	{
		if (PIND & (1 << PORTD3)){
			debounce();
			power++;
		}

		PORTB = power;
		if (power >= 16)
			power = 0;
	}
	return 0;
}
