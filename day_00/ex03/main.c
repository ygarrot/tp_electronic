#include <avr/io.h>

/* our wait. According to this page - http://playground.arduino.cc/Main/AVR, a NOP operation takes 1 clock cycle - 1 clock cycle = 1/frequency. At 16MHz a NOP will take 62.5nS to execute */
int main()
{
	DDRB |= (1 << PB3);
	for (;;)
	{
		for (long i = 0; i < 1600000; i++);
		PORTB ^= (1 << PB3);
	}
	return 0;
}
