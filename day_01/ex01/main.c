#include <avr/io.h>
#include <util/delay.h>

void main(){ 
	/* LED PORT B1 (OC1A) en output*/
	DDRB |= (1 << DDB1);

	/* Register: TCCR1B */
	/* Name: Timer/Counter 1 Control Register B */
	/* Description: Set the timer mode. */

	/* | Mode | WGM13 | WGM12 | WGM11 | WGM10 | TimerMode of Operation */
	/* | 14   | 1     | 1     |   1   |   0    | Fast PWM ICR1 BOTTOM TOP */
	TCCR1B = (1 << CS12) | (1 << CS10);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);

	/* Register: TCCR1A */
	/* Name: Timer/Counter 1 Control Register A */
	/* Description: Set the timer mode. */
	TCCR1A = (1 << WGM11); //bascule sortie a chaque comparaison
	TCCR1A |= (1 << COM1A1);

	ICR1 = 7812; // F_CPU / 1024 / 2
	OCR1A = ICR1 / 10;
	while(1);

}
