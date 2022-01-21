#include "tools.h"
#include <util/delay.h>

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

int main() {
	int8_t i = 0;
	const t_rgb colors[3] = {
		{ .r = 0xf2, .g = 0x18, .b = 0x4f },
		{ .r = 0x19, .g = 0xe0, .b = 0xa1 },
		{ .r = 0x4b, .g = 0x00, .b = 0x82 },
	};

	GLOBAL_INTERRUPT;

	timer1_pwm();
	timer0_pwm();
	D2_INPUT;
	DDRD |= PORT_OUTPUT(D, 6) | PORT_OUTPUT(D, 5) | PORT_OUTPUT(D, 3);

	PORTD = 0xff;
	while(1) {
		if (!(PIND & (1 << PIND2))) {
			while (!(PIND & (1 << PIND2)));
			i = (i + 1) % 3;
			const t_rgb test = colors[i];
			set_red(test.r);
			set_green(test.g);
			set_blue(test.b);
			_delay_ms(1000);
		}
	}
}

