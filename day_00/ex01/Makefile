MCU=atmega328p
CC=avr-gcc
OBJCOPY=avr-objcopy
F_CPU=16000UL
CFLAGS= -Wall -DF_CPU=${F_CPU} -mmcu=${MCU}
TARGET=main


all: hex flash

hex:
	avr-gcc ${CFLAGS} -I.. -o ${TARGET}.bin ${TARGET}.c 
	avr-objcopy -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	avrdude -b 115200 -p ${MCU} -c arduino -U flash:w:${TARGET}.hex:i -P /dev/ttyUSB*

clean:
	rm -f *.hex *.bin
