MEMORY {
	rom (rx)  : ORIGIN = 0x20000000, LENGTH = 64K
	ram (rwx) : ORIGIN = 0x20080000, LENGTH =  32K
}

SECTIONS {
    .text ORIGIN(rom): {
        *(.text*)
        . = ALIGN(4);
        __etext = .;
    }
}