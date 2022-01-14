#include "tools.h"

MY_ISR(TIMER0_COMPA_vect) {
	static uint8_t inc = 0;
	static uint8_t ratio = 0;

	ratio += inc ? 1 : -1;
	if ((!inc && ratio == 0)
		|| (inc && ratio == N_STEP))
		inc = !inc;
	OCR1A = ratio;
}

void init_timer_1_duty_cycle() {
	TCCR1B = PRESCALE_64;

	// turn on FAST PWM mode
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);
	TCCR1A = (1 << WGM11);

	// trigger every n_step
	TCCR1A |= (1 << COM1A1);

	ICR1 = N_STEP;
	OCR1A = 0;
}

void init_timer0() {
	TCCR0B = PRESCALE_256;
	// turn on CTC mode
	TCCR0A = (1 << WGM01);
	// trigger on release
	TIMSK0 = (1 << OCIE0A);

	// trigger every n_step
	OCR0A = N_STEP;
}

int main() {
	B_OUTPUT(1);
	D3_INPUT;
	GLOBAL_INTERRUPT;

	init_timer_1_duty_cycle();
	init_timer0();

	while (1);
}
