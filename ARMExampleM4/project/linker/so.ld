MEMORY {
	rom (rx)  : ORIGIN = 0x20000000, LENGTH = 64K
	ram (rwx) : ORIGIN = 0x20080000, LENGTH =  32K
}

VECTOR_SIZE = DEFINED(VECTOR_SIZE) ? VECTOR_SIZE : 180;

SECTIONS {
    .text ORIGIN(rom): {
        . = ALIGN(4);
        __Vectors = .;
        KEEP(*(.so_vectors))  /* Vector table */
        . = . + VECTOR_SIZE;
        . = ALIGN(4);
        *(.text*)           /* Program code */
        *(.so_start*)
        __so_etext = .;
    }
}