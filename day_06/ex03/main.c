#include "tools.h"

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_TXT "color: "
#define VAL_TXT " || value: "
#define RED_TXT "RED"
#define GREEN_TXT "GREEN"
#define BLUE_TXT "BLUE"

int8_t i = 0;

char buffer[20];


ISR(TIMER0_COMPA_vect) {
	PORTD = ~RED;
}

ISR(TIMER0_COMPB_vect) {
	PORTD = ~GREEN;
}

ISR(TIMER1_COMPA_vect) {
	PORTD = ~BLUE;
}

void println(char *str) {
	uart_printstr(str);
	uart_printstr("\r\n");
}
void display(char *color) {
	uart_printstr(COLOR_TXT);
	uart_printstr(color);
	uart_printstr(VAL_TXT);
	println(buffer);
}

void red() {
	display(RED_TXT);
	set_red(ADC);
}

void green() {
	display(GREEN_TXT);
	set_green(ADC);
}

void blue() {
	display(BLUE_TXT);
	set_blue(ADC);
}

void display_val_lvl() {
	int8_t ratio = calc_percent(ADC, 1023.0);
	PORTB = 0x00;
	if (ratio >= 99)
		PORTB |= 1 << PORTB3;
	if (ratio >= 75)
		PORTB |= 1 << PORTB2;
	if (ratio >= 50)
		PORTB |= 1 << PORTB1;
	if (ratio >= 25)
		PORTB |= 1 << PORTB0;
}

void set_rgb() {
	const void (*f[3])(void) = {
		red,
		green,
		blue
	};

	itoa(ADC, buffer, 10);
	f[i]();
}

ISR(ADC_vect) {
	ADCSRA |= (1 << ADSC) | (1 << ADIE);
	set_rgb();
	display_val_lvl();
}

void ADC_init()
{
	ADMUX = (1 << REFS0) | (4 & 0x07);

	ADCSRA = (1 << ADEN); //enable ADE
	ADCSRA |= (1 << ADIE); //interrupt
	ADCSRA |= (1 << ADIF);
	ADCSRA |= (1 << ADSC); //A2D CONVERTION

	ADCSRA |= (1 << ADPS2); //prescalers
	ADCSRA |= (1 << ADPS1); //prescalers
	ADCSRA |= (1 << ADPS0); //prescalers

}

void timer1_pwm() {
	TCCR1B = (1 << CS12) | (0 << CS11) | (1 << CS10);

	TCCR1B |= (1 << WGM12);
	TCCR1A |= (1 << WGM12);
	TIMSK1 |= (1 << OCIE1A);
}

void timer0_pwm() {
	TCCR0B = (1 << CS12) | (0 << CS11) | (1 << CS10);

	TCCR0B |= (1 << WGM02);
	TCCR0A |= (1 << WGM00);

	TIMSK0 |= (1 << OCIE0A);
	TIMSK0 |= (1 << OCIE0B);
}

int main() {
	/* GLOBAL_INTERRUPT; */

	timer1_pwm();
	timer0_pwm();
	D2_INPUT;
	B_OUTPUT_FULL;
	DDRD |= PORT_OUTPUT(D, 6) | PORT_OUTPUT(D, 5) | PORT_OUTPUT(D, 3);

	PORTD = 0xff;

	uart_init(8);
	ADC_init();
	sei();
	PORTD = 0xff;
	while(1) {
		if (!(PIND & (1 << PIND2))) {
			while (!(PIND & (1 << PIND2)));
			i = (i + 1) % 3;
		}
	}
}

