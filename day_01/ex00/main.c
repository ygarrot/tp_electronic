#include <avr/io.h>
void main(){ 
  /* LED PORT B1 (OC1A) en output*/
  DDRB |= (1 << DDB1);

  /* Register: TCCR1B */
  /* Name: Timer/Counter 1 Control Register B */
  /* Description: Set the timer mode. */

  TCCR1B = (1 << CS12) | (1 << CS10);
  /* TCCR1B = (1 << CS10); */
  /* Compare Match (CTC) Mode */

  /* -------------------------------------------------------------- */
  /* |Mode | WGM13 | WGM12 | WGM11 | WGM10 | TimerMode of Operation */
  /* -------------------------------------------------------------- */
  /* |  4  |   0   |   1   |   0   |   0   | CTC OCR1A Immediate MAX */
  /* -------------------------------------------------------------- */
  /* In CTC mode the counter is cleared to zero when the counter value (TCNT0) matches the OCR0A */
  TCCR1B |= (1 << WGM12);

  /* Register: TCCR1A */
  /* Name: Timer/Counter 1 Control Register A */
  /* Description: Set the timer mode. */
  TCCR1A = (1 << COM1A0);
  /* • Bit 5:4 – COM1B1:0: Compare Output Mode for Channel B */

  OCR1A = 7812; //16 000 000 / (1024 * 2)
  while(1);
}
