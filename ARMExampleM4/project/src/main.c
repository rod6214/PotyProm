#include "so.h"
#include "gpio.h"

extern unsigned int _estack;
extern unsigned int _sfixed;

int main();
void Reset_Handler(void);
void SVC_Handler(int);

__attribute__ ((section(".entry")))
void entry_point() 
{
    main();
}

__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
    .pvStack = (void*) (&_estack),
    .pfnReset_Handler = Reset_Handler,
    .pfnSVC_Handler = SVC_Handler
};

void ___syscall(int code) 
{
    asm("mov r0, %0"::"r"(code));
    asm("svc 1");
}

void Reset_Handler() 
{
    portB_as_output(P27);
    
}

void SVC_Handler(int code) 
{
    if (code == 2)
        set_HIGH_portB(P27);
    if (code == 3)
        set_LOW_portB(P27);
}

int main() {
    // Subs_t subs;
    // subs.code = 1;
    // add_syscall_subscriber(subs);
    ___syscall(2);
    ___syscall(3);
    while(1) {}
    return 0;
}

