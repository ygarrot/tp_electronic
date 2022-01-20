#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <util/delay.h>
#include <avr/io.h>

/* https://github.com/amirbawab/AVR-cheat-sheet */
/* ########################## DAY 0 ########################## */

#define PORT_OUTPUT(PORT, n) (1 << DD ## PORT ## n )

#define B_OUTPUT_(n) (1 << DDB ## n )
#define B_OUTPUT(n) DDRB |= B_OUTPUT_(n)
#define B_OUTPUT_FULL DDRB |= B_OUTPUT_(1)| B_OUTPUT_(2) |B_OUTPUT_(3) | B_OUTPUT_(4)
/* pint 3 port b en output */
#define B3_OUTPUT B_OUTPUT(3)

#define TOGGLE_PORT_B3 PORTB ^= (1 << PORTB3)
#define CLEAR_PORT_B3 PORTB &= ~(1 << PORTB3);
#define SET_PORT_B3 PORTB |= (1 << PORTB3);

/* pin 2 port d en input */
#define D2_INPUT DDRC &= ~(1 << PORTD2)
#define PIND2_IS_UP (!(PIND & (1 << PIND2)))

#define HZ1 1600000
#define delay(n) for (long i = 0; i < n; i++);
#define DEBOUNCE(f) if (PIND3_IS_UP) { \
	while(PIND3_IS_UP); \
	f;\
	delay(500);\
}

/* ########################## END DAY 0 ########################## */

/* ########################## DAY 2 ########################## */

/* • Bit 7 – I: Global Interrupt Enable */

/* The Global Interrupt Enable bit must be set for the interrupts to be enabled. */

/* The individual interrupt enable control is then performed in separate control registers. */

/* If the Global Interrupt Enable Register is cleared, none of the interrupts */
/* are enabled independent of the individual interrupt enable settings. */

/* The I-bit is cleared by hardware after an interrupt has occurred, */
/* 	and is set by the RETI instruction to enable subsequent interrupts. */

/* The I-bit can also be set and cleared by the application with the SEI */
/* and CLI instructions, as described in the instruction set reference. */

#define GLOBAL_INTERRUPT SREG = (1 << 7);
#define DISABLE_GLOBAL_INTERRUPT SREG &= ~(1 << 7);

/* EX02 */

#define N_STEP 250
#define PRESCALE_256 (1 << CS02) | (0 << CS01) | (0 << CS00)
#define PRESCALE_64 (0 << CS02) | (1 << CS01) | (1 << CS00)

/* warning: ‘__INTR_ATTRS’ attribute directive ignored [-Wattributes] */
/* void vector (void) __attribute__ ((signal, __INTR_ATTRS));\ */
#define MY_ISR(vector) \
void vector (void) __attribute__ ((signal));\
void vector (void)

/* ########################## END DAY 2 ########################## */

/* ########################## DAY 3 ########################## */

#define UART_BAUDRATE 115200
#define UBRR F_CPU / 16 / UART_BAUDRATE - 1



/* 20.11.2 UCSRnA – USART Control and Status Register n A */
/* +---------------+------+-------+-----+------+------+------+-------+--------+ */
/* |     RXCn      | TXCn | UDREn | FEn | DORn | UPEn | U2Xn | MPCMn | UCSRnA | */
/* +---------------+------+-------+-----+------+------+------+-------+--------+ */
/* | Read/Write    | R    | R/W   | R   | R    | R    | R    | R/W   | R/W    | */
/* | Bit           | 7    | 6     | 5   | 4    | 3    | 2    | 1     | 0      | */
/* | Initial Value | 0    | 0     | 1   | 0    | 0    | 0    | 0     | 0      | */
/* +---------------+------+-------+-----+------+------+------+-------+--------+ */

/* • Bit 5 – UDREn: USART Data Register Empty */
/* The UDREn Flag indicates if the transmit buffer (UDRn)
   is ready to receive new data. If UDREn is one, the */
/* buffer is empty, and therefore ready to be written.

   The UDREn Flag can generate a Data Register Empty */
/* interrupt (see description of the UDRIEn bit).
   UDREn is set after a reset to indicate that the Transmitter is ready. */

#define TRANSMIT_BUFFER_NOT_READY (!(UCSR0A & (1 << UDRE0)))

void uart_tx(char c){
	while TRANSMIT_BUFFER_NOT_READY;
	/* Put data into buffer, sends the data */
	UDR0 = c;	
}

void uart_init(unsigned int ubrr) {
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8-bit, 1 stop bit */
	UCSR0C = (3 << UCSZ00);
}

/* Table 20-10. USBS Bit Settings */
/* +-------+-------------+ */
/* | USBSn | Stop Bit(s) | */
/* +-------+-------------+ */
/* |     0 | 1-bit       | */
/* |     1 | 2-bit       | */
/* +-------+-------------+ */

/* Table 20-11. UCSZn Bits Settings */
/* +--------+--------+--------+----------------+ */
/* | UCSZn2 | UCSZn1 | UCSZn0 | Character Size | */
/* +--------+--------+--------+----------------+ */
/* |      0 |      0 |      0 | 5-bit          | */
/* |      0 |      0 |      1 | 6-bit          | */
/* |      0 |      1 |      0 | 7-bit          | */
/* |      0 |      1 |      1 | 8-bit          | */
/* |      1 |      0 |      0 | Reserved       | */
/* |      1 |      0 |      1 | Reserved       | */
/* |      1 |      1 |      0 | Reserved       | */
/* |      1 |      1 |      1 | 9-bit          | */
/* +--------+--------+--------+----------------+ */

void timer_init(){ 
	TCCR1B = (1 << CS12) | (1 << CS10);
	TCCR1B |= (1 << WGM12);

	TCCR1A = (1 << COM1A0);
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt

	OCR1A = 15624; //16 000 000 / (1024) 1 hz
}

/* EX01 */

void uart_printstr(const char* str);

void uart_printstr(const char* str)
{
	while (*str)
	{
		uart_tx(*str);
		++str;
	}
}

/* EX02 */

void uart_printstr(const char* str);
char uart_rx(void);

char uart_rx(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}


/* ########################## END DAY 3 ########################## */

/* ########################## DAY 5 ########################## */

#define BLACK 0xff
#define WHITE 0x00
#define RED (1 << PORTD6)
#define GREEN (1 << PORTD5)
#define BLUE (1 << PORTD3)
#define YELLOW ~(RED | GREEN)
#define MAGENTA ~(RED | BLUE)
#define CYAN ~(GREEN | BLUE)



/* ########################## END DAY 5 ########################## */

#endif
