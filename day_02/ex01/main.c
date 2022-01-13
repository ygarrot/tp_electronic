#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define N_STEP 250
#define PRESCALE_256 (1 << CS02) | (0 << CS01) | (0 << CS00)
#define PRESCALE_64 (0 << CS02) | (1 << CS01) | (1 << CS00)

void TIMER0_COMPA_vect (void) __attribute__ ((signal));

void TIMER0_COMPA_vect (void) {
	static uint8_t inc = 0;
	static uint8_t ratio = 0;

	if (inc)
		ratio++;
	else
		ratio--;
	if (!inc && ratio == 0
		|| inc && ratio == N_STEP)
		inc = !inc;
	OCR1A = ratio;
}

void duty_cycle() {
	TCCR1B = PRESCALE_64;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);

	TCCR1A = (1 << WGM11);
	TCCR1A |= (1 << COM1A1);
	ICR1 = N_STEP;
	OCR1A = 0;
}

void init() {
	// clk / 256 bits
	TCCR0B = PRESCALE_256;
	// turn on CTC mode
	TCCR0A = (1 << WGM01);
	// trigger on release
	TIMSK0 = (1 << OCIE0A);

	//(16*10^6) / (1000*64) - 1
	OCR0A = N_STEP;
	SREG = (1 << 7);
}

int main() {
	DDRB = (1 << DDB3);
	DDRB |= (1 << DDB1);

	duty_cycle();
	init();

	while (1);
}
