#include <avr/io.h>

int main()
{
	unsigned power = 0;
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);
	DDRC &= ~(1 << PORTD3);
	while (1)
	{
		if (PIND & (1 << PORTD3)){
			power++;
		}

		if (power & 0b0001)
			PORTB |= (1 << PORTB1);
		else 
			PORTB &= (1 << PORTB1);

		if (power & 0b0010)
			PORTB |= (1 << PORTB2);
		else 
			PORTB &= (1 << PORTB2);

		if (power & 0b0100)
			PORTB |= (1 << PORTB3);
		else 
			PORTB &= (1 << PORTB3);

		if (power >= 8)
			power = 0;
	}
	return 0;
}
