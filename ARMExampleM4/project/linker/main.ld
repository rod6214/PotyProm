MEMORY {
	rom (rx)  : ORIGIN = 0x00080000, LENGTH = 512K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH =  86K
}

/* The stack size used by the application. NOTE: you need to adjust according to your application. */
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : 0x400;

/* The heapsize used by the application. NOTE: you need to adjust according to your application. */
HEAP_SIZE = DEFINED(HEAP_SIZE) ? HEAP_SIZE : 0x200;

SO_SIZE = DEFINED(SO_SIZE) ? SO_SIZE : 0x10000;

INCLUDE memorydef.ld
