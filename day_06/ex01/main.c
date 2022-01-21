#include "tools.h"

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP (int8_t)(((float)ADC - 324.31 ) / 1.22)

ISR(ADC_vect) {
	char buffer[20];
	ADCSRA |= (1 << ADSC) | (1 << ADIE);
	itoa(TEMP, buffer, 10);
	uart_printstr(buffer);
	uart_printstr("\r\n");
}

/* ADIF = ADC Interrupt Flag */
/* ADIE: ADC Interrupt Enable */
/* ADEN: ADC Enable */
/* Selecting the ADC8 channel by writing the MUX3...0 bits in ADMUX register to "1000" enables */
/* the temperature sensor. The internal 1.1V voltage reference must also be selected for the ADC voltage */
/* reference source in the temperature sensor measurement. W */
void ADC_init()
{
	ADMUX = (1 << REFS1) |(1 << REFS0) | (1 << MUX3);

	ADCSRA = (1 << ADEN); //enable ADE
	ADCSRA |= (1 << ADIE); //interrupt
	ADCSRA |= (1 << ADIF); //interupt
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

