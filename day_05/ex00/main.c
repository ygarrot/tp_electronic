#include "tools.h"
#include "time.h"
#include <avr/eeprom.h>
#include <util/delay.h>

#define col (const int8_t []) {~RED, ~GREEN, ~BLUE, YELLOW, MAGENTA, CYAN, WHITE}

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

