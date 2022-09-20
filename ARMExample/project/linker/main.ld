SECTIONS
{
. = 0x00080000;
.text : { *(.text) }
. = 0x20000000;
.data : { *(.data) }
.bss : { *(.bss) }
}