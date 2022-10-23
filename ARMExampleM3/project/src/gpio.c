// #include "so.h"
// #include "gpio.h"

void portB_as_output(unsigned int port) 
{
    // volatile unsigned int* PIO_PER_B_t = ___AT(PIO_PER_B);
    // volatile unsigned int* PIO_OER_B_t = ___AT(PIO_OER_B);
    // volatile unsigned int* PMC_PCER0_t = ___AT(PMC_PCER0);
    // *PIO_PER_B_t = port;
    // *PIO_OER_B_t = port;
    // *PMC_PCER0_t = PIOB_ID;
}

void set_HIGH_portB(unsigned int port)
{
    // volatile unsigned int* PIO_SODR_B_t = ___AT(PIO_SODR_B);
    // *PIO_SODR_B_t = port;
    asm("nop");
}

void set_LOW_portB(unsigned int port)
{
    // volatile unsigned int* PIO_CODR_B_t = ___AT(PIO_CODR_B);
    // *PIO_CODR_B_t = port;
}
