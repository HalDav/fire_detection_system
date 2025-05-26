# Target
TARGET = main

# MCU a frekvence
MCU = atmega328p
F_CPU = 16000000UL

# Toolchain
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Soubory
SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)

# CFLAGS
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -std=c11 -Isrc

# Výstupy
ELF = $(TARGET).elf
HEX = $(TARGET).hex

# Port a programátor (uprav podle potřeby)
AVRDUDE_MCU = m328p
AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT = COM4
AVRDUDE_BAUD = 115200

.PHONY: all flash clean

all: $(HEX)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(ELF): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(HEX)
	$(AVRDUDE) -p $(AVRDUDE_MCU) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PORT) -b $(AVRDUDE_BAUD) -U flash:w:$(HEX):i

clean:
	rm -f src/*.o $(ELF) $(HEX)
