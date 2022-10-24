#include "so.h"

IRQn_Type __irq;

static void __enable_interrupt() 
{
    switch (__irq)
    {
        case RTC_IRQn:
            {
                NVIC_EnableIRQ(RTC_IRQn);
            }
            break;
        
        default:
            break;
    }
}

void enable_IRQn(IRQn_Type irq) 
{
    __irq = irq;
    Subs_t irq_sub = { SYSCALL_ID, __enable_interrupt };
    add_subscriber(irq_sub);
    asm("svc 1");
}
