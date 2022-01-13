#include <util/delay.h>
#include <avr/io.h>

void debounce (state) {
	while (PIND & (1 << PORTD3)) {
	}
	PORTB ^= 1 << PORTB3;
	_delay_ms(1000);
	/* for (long i = 0; i < 160000000; i++); */
}

int main()
{
	DDRB |= (1 << DDB3);
	DDRC &= ~(1 << PORTD3);
	while (1){
		if(PIND & (1 << PORTD3))
			debounce();
	}
	return 0;
}
