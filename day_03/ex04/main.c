#include "tools.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define NL "\n\r"
#define USERNAME "admin"
#define PASSWORD "admin"
#define GREETING           "Bonjour ! Entrez votre login:" NL
#define NAME_TEXT     "\tusername: "
#define PASSWORD_TEXT "\tpassword: "
#define BAD_INPUT "Mauvaise combinaison username/password ." NL
#define VALID "Coucou " USERNAME " !" NL
#define TRUE 1 
#define FALSE 0

uint8_t compare(char *comp, int8_t display) {
	char buf[128];
	uint8_t i = 0;

	while (TRUE) {
		char c = uart_rx();
		if (c == '\r') {
			buf[i] = '\0';
			return strcmp(buf, comp) == 0;
		}
		if (i > 0 && (c == 0x7F)){
			uart_printstr("\b \b");
			buf[i--] = '\0';
		} else if (isprint(c)) {
			uart_tx(display ? c : '*');
			buf[i++] = c;
		}
	}
}

uint8_t compare_input(char *message, char *comp, int8_t display) {
	uint8_t ret = TRUE;

	uart_printstr(message);
	ret = compare(comp, display);
	uart_printstr(NL);
	return ret;
}

int main() {
	uint8_t duo_valid = FALSE;
	DDRB |= (1 << DDB0);
	DDRB |= (1 << DDB1);
	DDRB |= (1 << DDB2);
	DDRB |= (1 << DDB3);
	uart_init(8);

	while(1){
		uart_printstr(GREETING);
		duo_valid = compare_input(NAME_TEXT, USERNAME, TRUE)
			& compare_input(PASSWORD_TEXT, PASSWORD, FALSE);
		uart_printstr(duo_valid ? VALID NL : BAD_INPUT NL);
		if (duo_valid) {
			for (uint8_t i = 0; i <= 17; i++){
				PORTB = i;
				delay(160000);
			}
		}
	};
}
