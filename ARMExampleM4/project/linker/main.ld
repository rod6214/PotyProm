MEMORY {
	rom (rx)  : ORIGIN = 0x00080000, LENGTH = 512K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH =  32K
}

INCLUDE memorydef.ld
