SECTIONS {
	.text ORIGIN(rom) :
	{
		. = ALIGN(4);
		KEEP(*(.vectors))  /* Vector table */
		*(.text*)          /* Program code */
		*(.rodata*)        /* Read only data */
		__etext = .;
	}

	.__so ORIGIN(ram) : {
		. = ALIGN(8);
		__so_start__ = .;
		*(.__so*)      /* Read-write initialized data */
		. = . + SO_SIZE;
		__so_end__ = .;
	}

	.stack ADDR (.__so) + ADDR (.text):
	{
		. = ALIGN(8);
		__stack_start__ = .;
		*(.stack*)      /* Read-write initialized data */
		. = . + STACK_SIZE;
		__stack_end__ = .;
	}
}


/* __StackTop = ORIGIN(ram) + LENGTH(ram); */
/* __StackTop = AT ( ADDR (.text) + SIZEOF (.text) ); */
__text_size = SIZEOF (.text);
/* __data_size = SIZEOF (.data); */
/* __bss_size  = SIZEOF (.bss); */
__StackTop = ADDR(.stack) + SIZEOF(.stack);