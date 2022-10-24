#include "so.h"

IRQn_Type __irq;
int status;

static void __enable_interrupt() 
{
    if (!status)
        return;
    NVIC_EnableIRQ(__irq);
    status = FALSE;
}

void enable_IRQn(IRQn_Type irq) 
{
    status = TRUE;
    __irq = irq;
    Subs_t irq_sub = { SYSCALL_ID, __enable_interrupt };
    add_subscriber(irq_sub);
    asm("svc 1");
}
