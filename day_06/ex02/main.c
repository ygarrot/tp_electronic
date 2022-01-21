#include "tools.h"

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ISR(ADC_vect) {
	char buffer[20];
	ADCSRA |= (1 << ADSC) | (1 << ADIE);
	itoa(ADC, buffer, 10);   // here 2 means binary
	uart_printstr(buffer);
	uart_printstr("\r\n");
}

/* ADIF = ADC Interrupt Flag */
/* ADIE: ADC Interrupt Enable */
/* ADEN: ADC Enable */
void ADC_init()
{
	// Select Vref=AVcc
	ADMUX = (1 << REFS0) | (4 & 0x07);
	/* ADMUX = (1 << REFS0); */

	ADCSRA = (1 << ADEN); //enable ADE
	ADCSRA |= (1 << ADIE); //interrupt
	ADCSRA |= (1 << ADIF);
	ADCSRA |= (1 << ADSC); //A2D CONVERTION

	ADCSRA |= (1 << ADPS2); //prescalers
	ADCSRA |= (1 << ADPS1); //prescalers
	ADCSRA |= (1 << ADPS0); //prescalers

}

int main() {
	DDRD = PORT_OUTPUT(D, 6) | PORT_OUTPUT(D, 5) | PORT_OUTPUT(D, 3);

	uart_init(8);
	ADC_init();
	sei();
	/* GLOBAL_INTERRUPT; */
	PORTD = 0xff;
	while(1);
}

