#include <avr/io.h>

void delay(unsigned long delay) {
  volatile unsigned long i = 0;
  for (i = 0; i < delay; i++) {
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
