#include <util/delay.h>
#include <avr/io.h>

void debounce () {
	while (PIND & (1 << PORTD3)) {
	}
	_delay_ms(1000);
}
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
