#define UART_BAUDRATE 115200
#define UBRR F_CPU/16/UART_BAUDRATE-1

#include <avr/io.h>
#include <avr/interrupt.h>

void uart_tx(const char *data);
/* void uart_printstr(const char* str); */
char uart_rx(void);

/* void USART_RX_vect (void) __attribute__ ((signal,__INTR_ATTRS)); */

/* void USART_RX_vect (void) { */
/* 	uart_printstr("Hello world!\n\r"); */
/* } */

int8_t is_lower(char c) {
	return c >= 'a' && c <= 'z';
}

int8_t is_upper(char c) {
	return c >= 'A' && c <= 'Z';
}

ISR(USART_RX_vect, ISR_BLOCK)
{
	const char diff = 'A' - 'a';
	char c = uart_rx();

	if (is_lower(c))
		c += diff;
	else if (is_upper(c))
		c -= diff;
	uart_tx(c);
}

void uart_printstr(const char* str)
{
	while (*str)
	{
		uart_tx(*str);
		++str;
	}
}
void uart_init(unsigned int ubrr) {
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Enable receiver interupt */
	UCSR0B |= (1 << RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void uart_tx(const char* data) {
	while (!(UCSR0A & (1 << UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;	
}

char uart_rx(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
		;
	/* Get and return received data from buffer */
	return UDR0;
}

int main() {
	DDRB |= (1 << DDB3);

	uart_init(8);
	sei();
	/* SREG = 1 << 7; */
	while(1){
		/* uart_tx(uart_rx()); */
	};
}
