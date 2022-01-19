#include "tools.h"

int main() {
	uart_init(8);
	while(1){
		uart_printstr("\n\rcharacter received: ");
		uart_tx(uart_rx());
	};
}
