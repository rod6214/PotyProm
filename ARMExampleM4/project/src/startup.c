#include "so.h"
#include "gpio.h"

extern unsigned int _estack;

int main();

__attribute__ ((section(".entry")))
void entry_point() 
{
    main();
}

__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
    .pvStack = (void*) (&_estack),
    .pfnReset_Handler = Reset_Handler,
    .pfnSVC_Handler = SVC_Handler,
    .pfnSysTick_Handler = SysTick_Handler
};

void ___syscall(int code) 
{
    asm("mov r0, %0"::"r"(code));
    asm("svc 1");
}
