#include <avr/io.h>
#define F_CPU 16000000UL


/* void main() { */
/* 	/1* port b 3 en output (led) *1/ */
/* 	DDRB |= (1 << DDB3); */

/* 	TCCR1B = (1 << CS12) | (1 << CS10); */

/* 	OCR1A = 7812; //16 000 000 /(1024*2) */
/* 	/1* TCNT1 = 1; *1/ */ 
/* 	while (1) { */
/* 		/1* tant que le flag d'overflow n'est pas actif on ne fait rien *1/ */
/* 		while((TIFR1 & (1 << OCF1A)) == 0); */
/* 		/1* on inverse l'etat de la led *1/ */
/* 		PORTB ^= 1 << PORTB3; */
/* 		/1* TCNT1 = 0; *1/ */ 
/* 		/1* reset du flag d'overflow *1/ */
/* 		TIFR1 |= (1<<OCF1A); */
/* 	} */
/* } */

void main(){ 
  DDRB |= (1 << DDB1);
  /* DDRB |= (1 << DDB3); */

  // 1 << 2 | 1 << 0 = 101 -> 1024 (Clock/1024)
  /* Register: TCCR1B */
  /* Name: Timer/Counter 1 Control Register B */
  /* Description: Set the timer mode. */

  TCCR1B = (1<<CS12) | (1<<CS10);
  TCCR1B |= (1<<WGM12); //RAZ timer quand comparaison

  /* Register: TCCR1A */
  /* Name: Timer/Counter 1 Control Register A */
  /* Description: Set the timer mode. */
  TCCR1A = (1<<COM1A0); //bascule sortie a chaque comparaison
  /* TCCR1A |= (1<<COM1B1); //bascule sortie a chaque comparaison */
  /* TCCR1A &= ~(1<<COM1B1); //bascule sortie a chaque comparaison */
  /* • Bit 5:4 – COM1B1:0: Compare Output Mode for Channel B */

  OCR1A = 7812;//16 000 000 /(1024*2)
  while(1);
}
