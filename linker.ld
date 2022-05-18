OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x0500;
    .text :
    {
        *(.text);
    }
    .data :
    {
        *(.data);
        *(.bss);
        *(.rodata);
    }
}