TARGET=flash
CC=arm-none-eabi-gcc
MACH=cortex-m0plus
FLOAT=soft
LINKER_SCRIPT=Linkers/STM32G0B1.ld

#DEFINES+= -DNDEBUG

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) -std=gnu11 -Wall -O0 -ggdb $(DEFINES)
LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) --specs=nano.specs -T $(LINKER_SCRIPT) -Wl,-Map=App/Build/$(TARGET).map -ggdb -u _printf_float -Wl,--print-memory-usage
OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES+= -I App/Inc/
INCLUDES+= -I Drivers/Inc/ 


############################################
# 				OUTPUT FILES

OBJS		+= App/Build/main.o
OBJS		+= App/Build/syscalls.o
OBJS		+= App/Build/startup.o
OBJS		+= App/Build/config.o

OBJS		+= App/Build/device.o

OBJS		+= App/Build/driver_systick.o
OBJS		+= App/Build/driver_gpio.o
OBJS		+= App/Build/driver_uart.o



all: App/Build App/Build/$(TARGET).elf 

App/Build:
	mkdir App/Build

App/Build/%.o: App/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o App/Src/$(*).c

App/Build/%.o: Src/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o App/Src/$(*).S

App/Build/%.o: Linkers/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o Linkers/$(*).c

App/Build/%.o: Drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o Drivers/Src/$(*).c

App/Build/%.o: Common/Src/utils/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o Common/Src/utils/$(*).c

App/Build/%.o: Common/Src/comms/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o App/Build/$(*).o Common/Src/comms/$(*).c

App/Build/$(TARGET).elf: $(OBJS) $(COMMS) $(UTILS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary App/Build/$(TARGET).elf App/Build/$(TARGET).bin
	arm-none-eabi-size App/Build/$(TARGET).elf

load:
	openocd -f interface/stlink-dap.cfg -f target/stm32g0x.cfg -c init -c "reset init" \
	-c "flash write_image erase App/Build/$(TARGET).elf" -c "reset run" -c shutdown

clean:
	rm -rf *.o *.map App/Build/*.o