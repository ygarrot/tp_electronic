#include "tools.h"
#include "time.h"
#include <avr/eeprom.h>
#include <util/delay.h>

#define col (const int8_t []) {~RED, ~GREEN, ~BLUE, YELLOW, MAGENTA, CYAN, WHITE}

#define WHITE 0x00
#define RED (1 << PORTD6)
#define GREEN (1 << PORTD5)
#define BLUE (1 << PORTD3)
#define YELLOW ~(RED | GREEN)
#define MAGENTA ~(RED | BLUE)
#define CYAN ~(GREEN | BLUE)

int main() {
	DDRD = PORT_OUTPUT(D, 6) | PORT_OUTPUT(D, 5) | PORT_OUTPUT(D, 3);

	int8_t i = 0;
	PORTD = 0xff;
	while(1) {
		if (!(PIND & (1 << PIND2))) {
			while (!(PIND & (1 << PIND2)));
			i = (i + 1) % sizeof(col);
			PORTD = col[i];
			_delay_ms(1000);
		}
	}
}

