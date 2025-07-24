CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu99
LDFLAGS = -nostdlib -T linker.ld -Wl,-Map=flash.map

all: flash.elf

main.o : main.c
	$(CC) $(CFLAGS) $^ -o $@
	
startup.o : startup.c
	$(CC) $(CFLAGS) $^ -o $@
	
flash.elf : main.o startup.o
	$(CC) $(LDFLAGS) $^ -o $@

load:
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
	-c "program flash.elf verify reset exit"

clean:
	rm *.o 