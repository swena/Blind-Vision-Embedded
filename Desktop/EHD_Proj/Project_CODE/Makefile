#run 'make blink.hex' to compile blink.c and prepare hex file rom.hex, then run 'make flash' to download the hex file.
.SUFFIXES: .hex .out
CC=avr-gcc
OBJCOPY=avr-objcopy

CFLAGS=-g -mmcu=atmega32 -Os

.out.hex:
	$(OBJCOPY) -j .text -O ihex $< rom.hex 
.o.out:
	$(CC) $(CFLAGS) -o $@ -Wl,-Map,rom.map $<
.c.o:
	$(CC) $(CFLAGS) -Os -c $<
all:$@



flash:rom.hex
	avrdude -p atmega32 -P /dev/ttyS0 -c stk500 -U flash:w:rom.hex

