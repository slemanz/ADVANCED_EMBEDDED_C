ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =256K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =60K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

_Min_Heap_Size = 0x200; 
_Min_Stack_Size = 0x400;

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        *(.text)         
        *(.text.*)         
        *(.rodata)        
        *(.rodata.*)        

        *(.eh_frame)

        . = ALIGN(4);
        _etext = .;       

        KEEP(*(.init))
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        /* C++ runtime constructors */
        . = ALIGN(4);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))

        /* C++ runtime destructors */
        . = ALIGN(4);
        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))
      . = ALIGN(4);

    } > FLASH


    _la_data = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        _sdata = .;   
        *(.data)           
        *(.data*)          
        *(.RamFunc)        
        *(.RamFunc*)       
        . = ALIGN(4);
        _edata = .;   
    } > SRAM AT> FLASH
    

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;    
        __bss_start__ = _sbss;
        
        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } > SRAM AT> FLASH 

    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } >SRAM

    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    .ARM.attributes 0 : { *(.ARM.attributes) }
}