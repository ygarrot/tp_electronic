#include "tools.h"

int main(){ 
	B_OUTPUT(1);

	/* +------+------+------+---------------------------+ */
	/* | CS12 | CS11 | CS10 | Description               | */
	/* |   1  |   0  |   1  | clk/1024 (From prescaler) | */
	/* +------+------+------+---------------------------+ */
	TCCR1B = (1 << CS12) | (0 << CS11) | (1 << CS10);

	/* +------+-------+-------+-------+-------+---------------+--------+-----------+-----------+ */
	/* | Mode | WGM13 | WGM12 | WGM11 | WGM10 | Timer/Counter |  Top   | Update of | TOV1 Flag | */
	/* |      |       |       |       |       |  mode of op   |        | OCR1x at  |  Set on   | */
	/* +------+-------+-------+-------+-------+---------------+--------+-----------+-----------+ */
	/* |  14  |   1   |   1   |   1   |   0   |    Fast PWM   |  ICR1  |  BOTTOM   |    TOP    | */
	/* +------+-------+-------+-------+-------+---------------+--------+-----------+-----------+ */
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);
	TCCR1A = (1 << WGM11);

	/* |      1  |      0  | Clear OC1A/OC1B on Compare Match (Set output to low level). | */
	TCCR1A |= (1 << COM1A1);

	/*            // F_CPU / (PRESCALE * 2) */
	ICR1 = 7812; // 16 000 000 / (1024 * 2)
	/* +--------+-----------+ */
	/* |  Top   | Update of | */
	/* |        | OCR1x at  | */
	/* +--------+-----------+ */
	/* |  ICR1  |  BOTTOM   | */
	/* +--------+-----------+ */
	OCR1A = ICR1 / 10;
	while(1);
}
