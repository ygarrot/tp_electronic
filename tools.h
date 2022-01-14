#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <util/delay.h>
#include <avr/io.h>

/* ########################## DAY 1 ########################## */

#define B_OUTPUT(n) DDRB |= (1 << DDB ## n )

/* pint 3 port b en output */
#define B3_OUTPUT B_OUTPUT(3)
/* pin 3 port d en input */
#define D3_INPUT DDRC &= ~(1 << PORTD3)


#define HZ1 1600000
#define delay(n) for (long i = 0; i < n; i++);
#define PIND3_IS_UP (PIND & (1 << PIND3))
#define TOGGLE_PORT_B3 PORTB ^= (1 << PORTB3);
/* pin 3 port b a 0 */
#define CLEAR_PORT_B3 PORTB &= ~(1 << PORTB3);
/* pin 3 port b a 1 */
#define SET_PORT_B3 PORTB |= (1 << PORTB3);

#define PIND3_IS_UP (PIND & (1 << PIND3))

#define DEBOUNCE(f) if PIND3_IS_UP { \
	while PIND3_IS_UP;\
	delay(HZ1 * 10);\
	f;\
}\

/* ########################## END DAY 1 ########################## */

#endif
