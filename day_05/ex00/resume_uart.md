USART: Moyen de communication tres flexible

The Power
Reduction USART bit, PRUSART0, in ”Minimizing Power Consumption” on page 51 must be disabled by writing
a logical zero to it.
\

# Les trois partie principale de l'USART
- Clock
4 mode de fonctionnement:
	- Normal asynchronous
	- Double Speed asynchronous (seulement asynchrone) <- controlled by U2Xn in UCSRnA Register
	- Master synchronous
	- Slave synchronous mode

The Transmitter divides the baud rate generator clock output by 2, 8 or 16 depending on mode

- Generator

- Transmitter and Receiver
