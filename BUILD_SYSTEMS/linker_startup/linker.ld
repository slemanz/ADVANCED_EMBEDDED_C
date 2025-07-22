/* 1. Entry Point */
ENTRY(Reset_Handler)

/* 2. Memory definitions */
MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =256K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =60K
}

_estack = ORIGIN(RAM) + LENGTH(RAM)

/* 3. Indicate required heap and stack size */
__max_heap_size = 0x200
__max_stack_size = 0x400

/* Sections */
SECTIONS
{

}