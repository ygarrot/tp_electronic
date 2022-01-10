#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= (1 << DDB3);
	DDRC &= ~(1 << 3);
	while (1)
	{
		if (PIND & (1 << PORTD3))
			PORTB &= ~(1 << PORTB3);
		else
			PORTB |= (1 << PORTB3);
	}
	return 0;
}
