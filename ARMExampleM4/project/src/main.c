#include "so.h"

int __START__ main() {
    volatile unsigned int* PIO_PER_B_t = ___AT(PIO_PER_B);
    volatile unsigned int* PIO_OER_B_t = ___AT(PIO_OER_B);
    volatile unsigned int* PMC_PCER0_t = ___AT(PMC_PCER0);
    volatile unsigned int* PIO_CODR_B_t = ___AT(PIO_CODR_B);
    volatile unsigned int* PIO_SODR_B_t = ___AT(PIO_SODR_B);

    *PIO_PER_B_t = P27;
    *PIO_OER_B_t = P27;
    *PMC_PCER0_t = PIOB_ID;
    
    __syscall(2);
    while(1){
        *PIO_CODR_B_t = P27;
        *PIO_SODR_B_t = P27;
    }
    return 0;
}
