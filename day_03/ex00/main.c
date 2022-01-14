#include "tools.h"

MY_ISR(TIMER1_COMPA_vect) {
	uart_tx('Z');
}

int main() {
	GLOBAL_INTERRUPT;
	timer_init();
	uart_init(8);
	while(1);
}

