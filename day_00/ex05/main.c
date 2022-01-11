#include <util/delay.h>
#include <avr/io.h>

void delay(unsigned long delay) {
	volatile unsigned long i = 0;
	for (i = 0; i < delay * 160; i++) {
		__asm__ __volatile__ ("nop");
	}
}

int debounce (unsigned last_state) {
	unsigned new_state = PIND & (1 << PORTD3);

	if( last_state != new_state )
	{
		_delay_ms(50);
		if( PIND & (1 << PORTD3) == new_state )
			return new_state;
	}

	return last_state ;
}

int main()
{
	unsigned last_state = PIND & (1 << PORTD3);
	DDRB |= (1 << DDB3);
	DDRC &= ~(1 << PORTD3);
	while (1)
	{

		_delay_ms(5000);
		/* last_state = debounce(last_state); */
		/* if (last_state) */
			PORTB ^= 1 << PORTB3;
	}
	return 0;
}
