#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= (1 << DDB1);
	while (1)
	{
		PORTB |= (1 << PORTB3);
		_delay_ms(1000);
		PORTB &= ~(1 << PORTB3);
		_delay_ms(1000);
	}
	return 0;
}
