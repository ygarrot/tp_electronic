#include <avr/io.h>

#define CLEAR_PORT_B3 PORTB &= ~(1 << PORTB3);
#define SET_PORT_B3 PORTB |= (1 << PORTB3);

#define PIND3_IS_UP PIND & (1 << PIND3)

int main()
{
	/* pint 3 port b en output */
	DDRB |= (1 << DDB3);
	/* pin 3 port d en input */
	DDRC &= ~(1 << PORTD3);
	while (1)
	{
		/* si le pin 3 du port d est up == bouton enclenche */
		if (PIND3_IS_UP)
			/* pin 3 port b a 0 */
			CLEAR_PORT_B3
		else
			/* pin 3 port b a 1 */
			SET_PORT_B3
	}
	return 0;
}
