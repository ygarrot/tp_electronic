#include <avr/io.h>

int main()
{
	/* Define pull-ups and set outputs high */
	/* Define directions for port pins */
	/* on indique que le bit 3 du port b est en output */
	DDRB |= (1 << DDB3);
	/* on indique que le bit 3 du port d est en input */
	DDRC &= ~(1 << PORTD3);
	while (1)
	{
		/* si le bit 3 du port d est a 1 ca veut dire que le bouton est appuye */
		if (PIND & (1 << PORTD3))
			PORTB &= ~(1 << PORTB3);
		else
			PORTB |= (1 << PORTB3);
	}
	return 0;
}
