#include <avr/io.h>

#define delay(n) for (long i = 0; i < n; i++);

int main()
{
	DDRB |= (1 << PB3);
	for (;;)
	{
		delay(1600000);
		/* for (long i = 0; i < 1600000; i++); */
		PORTB ^= (1 << PB3);
	}
}
