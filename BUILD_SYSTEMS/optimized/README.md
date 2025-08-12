# Generic Code

There are many ways to optimize code size beyond `-Os`, The `-Os`  should be the
last option to reduce code size.

For our simple blinky with printf retarget example: [main.c](App/Src/main.c).

Here are the linker and C flags:

```makefile
CFLAGS  = -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0

LDFLAGS = $(MACH) -mthumb $(FLOAT) --specs=nano.specs $(LINKER) $(MAP_FILE) \
          -u _printf_float -Wl,--print-memory-usage
```

Resulting binary size:

| Memory Region | Used Size | Region Size | %age Used |
| --- | --- | --- | --- |
| FLASH         |  26.092 B | 256 KB | 9.95% |
| RAM           |   2.232 B |  60 KB | 3.63% |


## Remove Float Print