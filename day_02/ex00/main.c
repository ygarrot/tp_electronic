#include "tools.h"

int main() {
	B3_OUTPUT;
	D3_INPUT;
	GLOBAL_INTERRUPT;

	/* |   0   |   1   | Any logical change on INT0 generates an interrupt request. | */
	EICRA = 1 << ISC11;

	while (1) {
		if (EIFR & (1 << INTF1)) {
			EIFR = (1 << INTF1);
			TOGGLE_PORT_B3;
		}
	}
	return 1;
}

/* +-------+-------+------------------------------------------------------------+ */
/* | ISC01 | ISC00 | Description                                                | */
/* +-------+-------+------------------------------------------------------------+ */
/* |   0   |   0   | The low level of INT0 generates an interrupt request.      | */
/* +-------+-------+------------------------------------------------------------+ */
/* |   0   |   1   | Any logical change on INT0 generates an interrupt request. | */
/* +-------+-------+------------------------------------------------------------+ */
/* |   1   |   0   | The falling edge of INT0 generates an interrupt request.   | */
/* +-------+-------+------------------------------------------------------------+ */
/* |   1   |   1   | The rising edge of INT0 generates an interrupt request.    | */
/* +-------+-------+------------------------------------------------------------+ */
