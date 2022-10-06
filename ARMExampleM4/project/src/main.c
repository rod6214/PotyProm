#include "so.h"
#include "gpio.h"

int state = 0;

void systick_configuration() 
{
    SYSTICK->CTRL = 7;
    SYSTICK->LOAD = 899999;
    SYSTICK->CALIB = 0xC0000000 | 21000;
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
    state = 0;

    // GPIO_t* gpio = GPIOC;

    // CLOCK_enable_GPIOC(RCC);
    // gpio->GPIOx_MODER = MODER9(2);
    // gpio->GPIOx_AFRH = 0;
    // CLOCK_start_default(RCC);

    // FMC_SDRAM_start_default(SDRAMC);

    int* space = (int*)SDRAM_BASE;
    int* pepe = (int*)0x20001000;
    *space = 45;
    // gpio->GPIOx_BSRR = (1 << 9);
    // Subs_t systickConfSubs = {SYSCALL_ID, systick_configuration};
    // Subs_t systickHadlerSubs = {SYSTICK_ID, systick_hadler};
    
    // // portB_as_output(P27);
    // reset_list();
    // add_subscriber(systickConfSubs);
    // add_subscriber(systickHadlerSubs);
    
    // ___syscall(1);
    
    while(1) {
        (*space)++;
        (*pepe) = (*space);
    }
    return 0;
}

