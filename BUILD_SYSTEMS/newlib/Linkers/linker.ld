ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =256K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =60K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

_Min_Heap_Size = 0x200; 
_Min_Stack_Size = 0x400;

/* Sections */
SECTIONS
{
    /*first section of output file*/
    .text :
    {
        . = ALIGN(4);
        *(.isr_vector)  /*merge all .isr_vector_tbl sections of input files*/
        *(.text)            /*merge all .text sections of input files*/
        *(.rodata)          /*merge all .rodata sections of input files*/
        . = ALIGN(4);
        _etext = .;         /*Create a global symbol to hold end of text section*/
    } > FLASH


    _la_data = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        _sdata = .;         /*Create a global symbol to hold start of data section*/
        *(.data)            /*merge all .data sections of input files*/
        . = ALIGN(4);
        _edata = .;         /*Create a global symbol to hold end of data section*/
    } > SRAM AT> FLASH
    

    /*third section of output file*/
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;          /*Create a global symbol to hold start of bss section*/
        __bss_start__ = _sbss;          /*Create a global symbol to hold start of bss section*/
        *(.bss)             /*merge all .bss sections of input files*/
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } > SRAM AT> FLASH /* > (vma) AT> (lma) */

    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } >SRAM
}