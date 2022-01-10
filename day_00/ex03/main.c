#include <avr/io.h>

/* our wait. According to this page - http://playground.arduino.cc/Main/AVR, a NOP operation takes 1 clock cycle - 1 clock cycle = 1/frequency. At 16MHz a NOP will take 62.5nS to execute */
void delay(unsigned long delay) {
  volatile unsigned long i = 0;
  multiply
  for (i = 0; i < delay * 160; i++) {
      __asm__ __volatile__ ("nop");
  }
}

void blink(void){
	const int ms = 500;
	PORTB |= (1 << PORTB3);
	delay(50000);
	PORTB &= ~(1 << PORTB3);
	delay(50000);
}

int main()
{
	DDRB |= (1 << DDB3);
	while (1)
	{
		blink();
	}
	return 0;
}
