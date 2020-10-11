# File:   Makefile
# Authors: William Chen, Troy Tomlins
# Date:   7th Oct
# Descr:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.

game.o: game.c game.h ../../drivers/avr/system.h ../../utils/tinygl.h ../../drivers/avr/ir_uart.h ../../utils/task.h shells.h ../../drivers/led.h player.h readyup.h ../../drivers/button.h gameover.h lives.h
	$(CC) -c $(CFLAGS) $< -o $@

shells.o: shells.c ../../utils/tinygl.h shells.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

readyup.o: readyup.c readyup.h ../../drivers/avr/ir_uart.h ../../utils/font.h ../../utils/tinygl.h ../../drivers/navswitch.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

task.o: ../../utils/task.c ../../utils/task.h ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/navswitch.h ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/avr/delay.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/ledmat.h ../../drivers/avr/system.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../utils/pacer.h ../../drivers/avr/timer.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/timer.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../utils/tinygl.h ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/display.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/timer0.h ../../drivers/avr/system.h ../../drivers/avr/bits.h ../../drivers/avr/prescale.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/usart1.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

player.o: player.c player.h shoot.h ../../drivers/navswitch.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

shoot.o: shoot.c shoot.h ../../utils/tinygl.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

gameover.o: gameover.c gameover.h
	$(CC) -c $(CFLAGS) $< -o $@
	
lives.o: lives.c lives.h gameover.h ../../utils/tinygl.h player.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
game.out: game.o system.o navswitch.o readyup.o lives.o pio.o button.o ledmat.o pacer.o timer.o tinygl.o display.o font.o ir_uart.o timer0.o usart1.o prescale.o led.o task.o shells.o player.o shoot.o gameover.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start

