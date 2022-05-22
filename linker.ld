OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x07E00;
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