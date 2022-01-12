#include <avr/io.h>
#include <util/delay.h>


void main(){ 
	DDRB |= (1 << DDB1);

	/* Register: TCCR1B */
	/* Name: Timer/Counter 1 Control Register B */
	/* Description: Set the timer mode. */

	TCCR1B = (1 << CS12) | (1 << CS10);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);

	/* Register: TCCR1A */
	/* Name: Timer/Counter 1 Control Register A */
	/* Description: Set the timer mode. */
	TCCR1A = (1 << WGM11); //bascule sortie a chaque comparaison
	TCCR1A |= (1 << COM1A1);

	/* • Bit 5:4 – COM1B1:0: Compare Output Mode for Channel B */
	ICR1 = 7812; // F_CPU / 1024 / 2
	OCR1A = 781;
	while(1);

}
