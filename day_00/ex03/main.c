#include "../tools.h"

int main()
{
	B3_OUTPUT;
	for (;;)
	{
		delay(HZ1);
		TOGGLE_PORT_B3
	}
}
