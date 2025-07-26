CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=gnu99 -Wall -O0

LINKER = -T Src/linker.ld
LDFLAGS = -nostdlib $(LINKER) -Wl,-Map=$(BUILD_DIR)/flash.map

BUILD_DIR = Build
PREREQ = $(BUILD_DIR)/

INCLUDES += -I Inc/

OBJS += $(BUILD_DIR)/main.o
OBJS += $(BUILD_DIR)/startup.o
OBJS += $(BUILD_DIR)/adc.o

all: $(PREREQ) $(BUILD_DIR)/flash.elf

$(PREREQ):
	mkdir $(PREREQ)

$(BUILD_DIR)/%.o : Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o Src/$(*).c
	
$(BUILD_DIR)/flash.elf : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

load:
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
	-c "program $(BUILD_DIR)/flash.elf verify reset exit"

clean:
	rm -rf $(BUILD_DIR)/*.o 