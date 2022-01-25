#include "tools.h"

#include "time.h"

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h> #include <string.h>

static int8_t send_signal = 0;
static int8_t cur_delay = 0;

ISR(ADC_vect) {
	char buffer[20];
	ADCSRA |= (1 << ADSC) | (1 << ADIE);
	itoa(ADC, buffer, 10);   // here 2 means binary
	uart_printstr(buffer);
	uart_printstr("\r\n");

}

void transmit() {
	// return while delay is not 0
	if (ms_counter >= 500)
		send_signal = 0;
	if (send_signal)
		return;
	PORTC = 0x00;
}

int main() {
	DDRC = PORT_OUTPUT(C, 1);
	B_OUTPUT_FULL;
	uart_init(8);
	ADC_init(PC5);
	sei();

	enable_tick_counter();
	PORTC = 0;
	PORTB = 0x0;
	while(1) {
		if (!(PIND & (1 << PIND2))) {
			ms_counter = 0;
			send_signal = 1;
			cur_delay = 500;
			PORTC = 0xff;
		}
		transmit();
	}
}

