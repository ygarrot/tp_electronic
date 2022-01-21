#include "tools.h"
#include <util/delay.h>

#define welc "enter a color" NL
#define color_set "color has been set" NL

MY_ISR(TIMER0_COMPA_vect) {
	PORTD = ~RED;
}

MY_ISR(TIMER0_COMPB_vect) {
	PORTD = ~GREEN;
}

MY_ISR(TIMER1_COMPA_vect) {
	PORTD = ~BLUE;
}

void timer1_pwm() {
	TCCR1B = (1 << CS12) | (0 << CS11) | (1 << CS10);

	TCCR1B |= (1 << WGM12);
	TCCR1A |= (1 << WGM12);
	TIMSK1 |= (1 << OCIE1A);
}

void timer0_pwm() {
	TCCR0B = (1 << CS12) | (0 << CS11) | (1 << CS10);

	TCCR0B |= (1 << WGM02);
	TCCR0A |= (1 << WGM00);

	TIMSK0 |= (1 << OCIE0A);
	TIMSK0 |= (1 << OCIE0B);
}

void get_color() {
	t_rgb rgb;
	char c = '\0';
	char buffer[8] = {};

	for (int8_t i = 0; c != '\r'; i++) {
		c = uart_rx();
		uart_tx(c);
		buffer[i] = c;
	}

	sscanf(buffer, "#%x%x%x", &rgb.r, &rgb.g, &rgb.b);

	set_red(rgb.r);
	set_green(rgb.g);
	set_blue(rgb.b);
	uart_printstr(color_set);
}

int main() {
	uart_init(8);
	int8_t i = 0;

	GLOBAL_INTERRUPT;

	timer1_pwm();
	timer0_pwm();
	D2_INPUT;

	D_FULL_OUPUT;
	PORTD = 0xff;
	while(1) {
		uart_printstr(welc);
		get_color();
	}
}

