#include <util/delay.h>
#include <avr/io.h>

int debounce () {
	unsigned new_state = PIND & (1 << PORTD3);

	while (PIND & (1 << PORTD3) == new_state){
	}
	for (long i = 0; i < 1600000; i++);
	PORTB ^= 1 << PORTB3;

	return last_state ;
}

int main()
{
	DDRB |= (1 << DDB3);
	DDRC &= ~(1 << PORTD3);
	while (1){
		if( PIND & (1 << PORTD3))
			debounce();
	}
	return 0;
}
