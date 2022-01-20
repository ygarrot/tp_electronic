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

typedef struct rgb {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} t_rgb;

#define inverse_ratio(n) (int8_t)(100.0 - (n / 255.0 * 100.0))
#define calc_ratio(n) freq * inverse_ratio(n) / 100;

#define set_red(n) OCR0A = calc_ratio(n);
#define set_green(n) OCR0B = calc_ratio(n);
#define set_blue(n) OCR1A = calc_ratio(n);

int main() {
	int8_t i = 0;
	const t_rgb colors[3] = {
		{ .r = 0xf2, .g = 0x18, .b = 0x4f },
		{ .r = 0x19, .g = 0xe0, .b = 0xa1 },
		{ .r = 0x4b, .g = 0x00, .b = 0x82 },
	};
	TCCR1B = (1 << CS12) | (0 << CS11) | (1 << CS10);
	TCCR0B = (1 << CS12) | (0 << CS11) | (1 << CS10);

	TCCR0B |= (1 << WGM02);
	TCCR0A |= (1 << WGM00);

	TCCR1B |= (1 << WGM12);
	TCCR1A |= (1 << WGM12);

	GLOBAL_INTERRUPT;

	// Enable CTC interrupt
	TIMSK1 |= (1 << OCIE1A);
	TIMSK0 |= (1 << OCIE0A);
	TIMSK0 |= (1 << OCIE0B);
	D2_INPUT;
	DDRD |= PORT_OUTPUT(D, 6) | PORT_OUTPUT(D, 5) | PORT_OUTPUT(D, 3);

	PORTD = 0xff;
	while(1) {
		int8_t freq = 50;
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

