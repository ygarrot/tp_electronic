#include "../tools.h"

int main()
{
	B3_OUTPUT;
	D3_INPUT;
	while (1) {
		DEBOUNCE(TOGGLE_PORT_B3);
	}
	return 0;
}
