#include "so.h"
#include "gpio.h"

int state = 0;

void operating_system();

void systick_configuration() 
{
    SYSTICK->CTRL = 7;
    SYSTICK->LOAD = 899999;
    SYSTICK->CALIB = 0xC0000000 | 21000;
}

void test() {
    int* space = (int*)SDRAM_BASE;
    *space = 45;
}

void systick_hadler() 
{
    if (state)
    {
        // set_LOW_portB(P27);
        state=0;
    }
    else
    {
        // set_HIGH_portB(P27);
        state=1;
    }
    
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
}

int main() {
    CLOCK_start_default();
    FMC_SDRAM_prepare_ports();
    FMC_SDRAM_start_default();
    BOOT_OperatingSystem(0xD0000101);
    while(1) {}
    return 0;
}
