#include <avr/io.h>

int main()
{
	/* bit 3 du port b en output */
	DDRB |= (1 << DDB3);
	/* pin 3 du port b a 1 pour allumer la led */
	PORTB = (1 << PORTB3);
	return 0;
}
