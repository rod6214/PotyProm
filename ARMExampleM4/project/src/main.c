#include "so.h"
#include "gpio.h"

int state = 0;

void systick_configuration() 
{
    SYSTICK->CTRL = 7;
    SYSTICK->LOAD = 8999999;
}

void systick_hadler() 
{
    if (state)
    {
        set_LOW_portB(P27);
        state=0;
    }
    else
    {
        set_HIGH_portB(P27);
        state=1;
    }
    
    asm("nop");
}

int main() {
    state = 0;
    Subs_t systickConfSubs = {SYSCALL_ID, systick_configuration};
    Subs_t systickHadlerSubs = {SYSTICK_ID, systick_hadler};
    portB_as_output(P27);
    reset_list();
    add_subscriber(systickConfSubs);
    add_subscriber(systickHadlerSubs);
    
    ___syscall(1);
    
    while(1) {}
    return 0;
}

