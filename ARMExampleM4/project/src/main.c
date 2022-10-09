#include "so.h"
#include "gpio.h"

SO_Input_t input;

#define CALL_OPERATING_SYSTEM(ptr) asm volatile ( \
        "mov r0, %0\n\t" \
        "ldr r1, =#0xD0000001\n\t" \
        "blx r1" \
        : \
        : "r"(&input))

int main() {    
    CLOCK_start_default();
    FMC_SDRAM_prepare_ports();
    FMC_SDRAM_start_default();

    input.syscall = ___syscall;
    input.add_subscriber = add_subscriber;
    input.remove_subscriber = remove_subscriber;

    CALL_OPERATING_SYSTEM(input);
    
    while(1) {}
    return 0;
}
