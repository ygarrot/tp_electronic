#include <avr/io.h>

int main()
{
	/* Define pull-ups and set outputs high */
	/* Define directions for port pins */
	/* on indique que le bit 3 du port b est en output */
	DDRB |= (1 << DDB3);
	/* on met le bit 3 (port 3) du port b a 1 pour allumer la led */
	PORTB = (1 << PORTB3);
	return 0;
}
