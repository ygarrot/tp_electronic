#include "tools.h"
/* https://github.com/amirbawab/AVR-cheat-sheet */

/* +---------+---------+-------------------------------------------------------------+ */
/* | COM1A1  | COM1A0  |                         Description                         | */
/* +---------+---------+-------------------------------------------------------------+ */
/* |      0  |      0  | Normal port operation, OC1A/OC1B disconnected.              | */
/* |      0  |      1  | Toggle OC1A/OC1B on Compare Match.                          | */
/* |      1  |      0  | Clear OC1A/OC1B on Compare Match (Set output to low level). | */
/* |      1  |      1  | Set OC1A/OC1B on Compare Match (Set output to high level).  | */
/* +---------+---------+-------------------------------------------------------------+ */

int main(){ 
	B_OUTPUT(1);
	/* |   1  |   0  |   1  | clk/1024 (From prescaler)                              | */
	TCCR1B = (1 << CS12) | (0 << CS11)| (1 << CS10);

	/* In CTC mode the counter is cleared to zero when the counter value (TCNT0) matches the OCR0A */
	/* |  4   |   0   |   1   |   0   |   0   |        CTC        | CCR1A  | Immediate |    MAX    | */
	TCCR1B |= (1 << WGM12);
	/* Clear OC1A/OC1B on Compare Match (Set output to low level). */ 
	TCCR1A = (1 << COM1A0);

	/*            // F_CPU / (PRESCALE * 2) */
	OCR1A = 7812; // 16 000 000 / (1024 * 2)
	while(1);
}

/* Register: TCCR1B */
/* Name: Timer/Counter 1 Control Register B */
/* Datasheet: 20.14.2. TC1 Control Register B */
/* Description: Set the timer mode. */
/* Value: */

/* +------+------+------+--------------------------------------------------------+ */
/* | CS12 | CS11 | CS10 | Description                                            | */
/* +------+------+------+--------------------------------------------------------+ */
/* |   0  |   0  |   0  | No clock source (Timer/Counter stopped)                | */
/* +------+------+------+--------------------------------------------------------+ */
/* |   0  |   0  |   1  | clk/1 (No prescaling)                                  | */
/* +------+------+------+--------------------------------------------------------+ */
/* |   0  |   1  |   0  | clk/8 (From prescaler)                                 | */
/* +------+------+------+--------------------------------------------------------+ */
/* |   0  |   1  |   1  | clk/64 (From prescaler)                                | */
/* +------+------+------+--------------------------------------------------------+ */
/* |   1  |   0  |   0  | clk/256 (From prescaler)                               | */
/* +------+------+------+--------------------------------------------------------+ */
/* |   1  |   0  |   1  | clk/1024 (From prescaler)                              | */
/* +------+------+------+--------------------------------------------------------+ */
/* |   1  |   1  |   0  | External clock source on T1 pin. Clock on falling edge | */
/* +------+------+------+--------------------------------------------------------+ */
/* |   1  |   1  |   1  | External clock source on T1 pin. Clock on rising edge  | */
/* +------+------+------+--------------------------------------------------------+ */

/* Timer 1 (TC1 16-bit) */
/* Register: TCCR1A */
/* Name: Timer/Counter 1 Control Register A */
/* Datasheet: 20.14.1. TC1 Control Register A */
/* Description: Set the timer mode. */
/* Value: */

/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* | Mode | WGM13 | WGM12 | WGM11 | WGM10 |   Timer/Counter   | TOP    | Update of | TOV1 Flag | */
/* |      |       |       |       |       | Mode of Operation |        | OCR1x at  |  Set on   | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  0   |   0   |   0   |   0   |   0   |      Normal       | 0xFFFF | Immediate |    MAX    | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  1   |   0   |   0   |   0   |   1   | PWM,Phase Correct | 0X00FF |    TOP    |  BOTTOM   | */
/* |      |       |       |       |       |       8-bit       |        |           |           | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  2   |   0   |   0   |   1   |   0   | PWM,Phase Correct | 0x01FF |    TOP    |  BOTTOM   | */
/* |      |       |       |       |       |       9-bit       |        |           |           | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  3   |   0   |   0   |   1   |   1   | PWM,Phase Correct | 0x03FF |    TOP    |  BOTTOM   | */
/* |      |       |       |       |       |       10-bit      |        |           |           | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  4   |   0   |   1   |   0   |   0   |        CTC        | CCR1A  | Immediate |    MAX    | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  5   |   0   |   1   |   0   |   1   | Fast PWM, 8-bit   | 0x00FF |  BOTTOM   |    TOP    | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  6   |   0   |   1   |   1   |   0   | Fast PWM, 9-bit   | 0x01FF |  BOTTOM   |    TOP    | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  7   |   0   |   1   |   1   |   1   | Fast PWM, 10-bit  | 0x03FF |  BOTTOM   |    TOP    | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  8   |   1   |   0   |   0   |   0   | PWM, Phase and    |  ICR1  |  BOTTOM   |  BOTTOM   | */
/* |      |       |       |       |       | Frequency Correct |        |           |           | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  9   |   1   |   0   |   0   |   1   | PWM, Phase and    | OCR1A  |  BOTTOM   |  BOTTOM   | */
/* |      |       |       |       |       | Frequency Correct |        |           |           | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  10  |   1   |   0   |   1   |   0   | PWM,Phase Correct |  ICR1  |    TOP    |  BOTTOM   | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  11  |   1   |   0   |   1   |   1   | PWM,Phase Correct | OCR1A  |    TOP    |  BOTTOM   | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  12  |   1   |   1   |   0   |   0   |        CTC        |  ICR1  | Immediate |    MAX    | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  13  |   1   |   1   |   0   |   1   |      Reserved     |   -    |     -     |     -     | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  14  |   1   |   1   |   1   |   0   |      Fast PWM     |  ICR1  |  BOTTOM   |    TOP    | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */
/* |  15  |   1   |   1   |   1   |   1   |      Fast PWM     | OCR1A  |  BOTTOM   |    TOP    | */
/* +------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+ */

