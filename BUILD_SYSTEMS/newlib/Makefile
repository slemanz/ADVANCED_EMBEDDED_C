CC=arm-none-eabi-gcc
MACH=cortex-m4
FLOAT=soft
LINKER_SCRIPT=Linkers/linker.ld
MAP_FILE=App/Build/final.map

FINAL_FILE=App/Build/final.elf
FLASH_FILE=App/Build/flash.bin

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) -std=gnu99 -Wall -O0 -ggdb
LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) --specs=nano.specs -T $(LINKER_SCRIPT) -Wl,-Map=App/Build/final.map -ggdb -u _printf_float -Wl,--print-memory-usage
OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES+= -I App/Inc/
INCLUDES+= -I Drivers/Inc/ 


############################################
# 				OUTPUT FILES

OBJS		+= App/Build/main.o
OBJS		+= App/Build/config.o
OBJS		+= App/Build/syscalls.o
OBJS		+= App/Build/startup.o


DRIVERS		+= App/Build/driver_fpu.o
DRIVERS		+= App/Build/driver_systick.o
DRIVERS		+= App/Build/driver_gpio.o
DRIVERS		+= App/Build/driver_uart.o

all: App/Build App/Build/final.elf

App/Build:
	mkdir App/Build

App/Build/%.o: App/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o App/Src/$(*).c

App/Build/%.o: Drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o Drivers/Src/$(*).c

App/Build/%.o: Linkers/*.c
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o Linkers/$(*).c

App/Build/final.elf: $(OBJS) $(DRIVERS) $(BSP)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary App/Build/final.elf App/Build/flash.bin
	arm-none-eabi-size App/Build/final.elf

load:
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
	-c "program App/Build/final.elf verify reset exit"

clean:
	rm -rf *.o App/Build/*.map App/Build/*.o