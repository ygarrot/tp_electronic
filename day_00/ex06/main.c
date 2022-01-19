#include "../tools.h"
#include <util/delay.h>

int main()
{
	int8_t power = 0;
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);

	while (1)
	{
		power++;
		_delay_ms(500000);
		PORTB = power;
		power = power % 17;
	}
	return 0;
}
