#include <util/delay.h>
#include <avr/io.h>

int debounce (unsigned last_state) {
	unsigned new_state = PIND & (1 << PORTD3);

	if( last_state != new_state )
	{
		_delay_ms(25);
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
		last_state = debounce(last_state);
		if (last_state)
			PORTB ^= 1 << PORTB3;
	}
	return 0;
}
