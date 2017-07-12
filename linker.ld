ENTRY(start)

SECTIONS 
{
    . = 1M;

    .boot :
    {
        *(.multiboot_header)
    }

    .data BLOCK(4k) : ALIGN(4k)
    {
        *(.data)
    }

    .rodata BLOCK(4k) : ALIGN(4k)
    {
        *(.rodata)
    }

    .text BLOCK(4k) : ALIGN(4k)
    {
        *(.text)
    }
    
    .bss BLOCK(4k) : ALIGN(4k)
    {
        *(.bss)
    }
}