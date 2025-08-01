CC=arm-none-eabi-gcc
MACH=cortex-m4
FLOAT=hard
LINKER_SCRIPT=linkers/STM32F411xC.ld
MAP_FILE=app/Build/final.map

FINAL_FILE=app/Build/final.elf
FLASH_FILE=app/Build/flash.bin

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) -std=gnu99 -Wall -O0 -ggdb
LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=$(FLOAT) --specs=nano.specs -T $(LINKER_SCRIPT) -Wl,-Map=app/Build/$(TARGET).map -ggdb -u _printf_float -Wl,--print-memory-usage
OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES+= -I app/Inc/
INCLUDES+= -I drivers/Inc/ 
INCLUDES+= -I bsp/Inc/ 


############################################
# 				OUTPUT FILES

OBJS		+= app/Build/main.o
OBJS		+= app/Build/config.o
OBJS		+= app/Build/syscalls.o
OBJS		+= app/Build/startup.o

OBJS		+= app/Build/sensor.o
OBJS		+= app/Build/actuator.o
OBJS		+= app/Build/concrete_mediator.o


DRIVERS		+= app/Build/driver_fpu.o
DRIVERS		+= app/Build/driver_systick.o
DRIVERS		+= app/Build/driver_gpio.o
DRIVERS		+= app/Build/driver_uart.o
DRIVERS		+= app/Build/driver_adc.o
DRIVERS		+= app/Build/driver_spi.o
DRIVERS		+= app/Build/driver_i2c.o

BSP			+= app/Build/led.o
BSP			+= app/Build/button.o

all: app/Build app/Build/final.elf

app/Build:
	mkdir app/Build

app/Build/%.o: app/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o app/Src/$(*).c

app/Build/%.o: drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o drivers/Src/$(*).c

app/Build/%.o: bsp/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o bsp/Src/$(*).c

app/Build/%.o: linkers/*.c
	$(CC) $(CFLAGS) $(INCLUDES) -o app/Build/$(*).o linkers/$(*).c

app/Build/final.elf: $(OBJS) $(DRIVERS) $(BSP)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary app/Build/final.elf app/Build/flash.bin
	arm-none-eabi-size app/Build/final.elf

load:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c init -c "reset init" \
	-c "flash write_image erase app/Build/final.elf" -c "reset run" -c shutdown

debug:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c init -c "reset init"

clean:
	rm -rf *.o app/Build/*.map app/Build/*.o