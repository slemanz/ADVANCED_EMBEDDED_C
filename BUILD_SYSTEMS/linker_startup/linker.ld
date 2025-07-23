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
    /*first section of output file*/
    .text :
    {
        *(.isr_vector_tbl)  /*merge all .isr_vector_tbl sections of input files*/
        *(.text)            /*merge all .text sections of input files*/
        *(.rodata)          /*merge all .rodata sections of input files*/
    } > FLASH


    /*second section of output file*/
    .data :
    {
        *(.data)            /*merge all .data sections of input files*/
    }
    

    /*third section of output file*/
    .bss :
    {
        *(.bss)             /*merge all .bss sections of input files*/
    } > SRAM AT> FLASH /* > (vma) AT> (lma) */
}