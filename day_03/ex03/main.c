#include <avr/interrupt.h>
#include "tools.h"

#define DIFF 'A' - 'a'

int8_t is_lower(char c) {
	return c >= 'a' && c <= 'z';
}

int8_t is_upper(char c) {
	return c >= 'A' && c <= 'Z';
}

ISR(USART_RX_vect, ISR_BLOCK)
{
	char c = uart_rx();

	if (is_lower(c))
		c += DIFF;
	else if (is_upper(c))
		c -= DIFF;
	uart_tx(c);
}

int main() {
	DDRB |= (1 << DDB3);

	uart_init(8);
	/* Enable receiver interupt */
	UCSR0B |= (1 << RXCIE0);
	sei();
	while(1);
}
