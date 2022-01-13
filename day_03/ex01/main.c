#define UART_BAUDRATE 115200
#define UBRR F_CPU/16/UART_BAUDRATE-1

#include <avr/io.h>
#include <util/delay.h>

void uart_tx(const char *data);
void uart_printstr(const char* str);

void TIMER1_COMPA_vect (void) __attribute__ ((signal,__INTR_ATTRS));

void TIMER1_COMPA_vect (void) {
	uart_printstr("Hello world!\n\r");
}

void uart_printstr(const char* str)
{
	while (*str)
	{
		uart_tx(*str);
		++str;
	}
}

void timer_init(){ 
	TCCR1B = (1 << CS12) | (1 << CS10);
	TCCR1B |= (1 << WGM12);

	TCCR1A = (1 << COM1A0);
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt

	OCR1A = 15624 * 2; //16 000 000 / (1024) 1 hz
	SREG = 1 << 7;
}

void uart_init(unsigned int ubrr) {
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void uart_tx(const char* data) {
	while (!(UCSR0A & (1 << UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;	
}

int main() {
	timer_init();
	uart_init(8);
	while(1){
	};
}
