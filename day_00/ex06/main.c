#include "../tools.h"
#include <util/delay.h>

int main()
{
	int8_t power = 0;
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);
	D3_INPUT;

	while (1)
	{
		DEBOUNCE(power++);
		PORTB = power;
		power = power % 17;
	}
	return 0;
}
