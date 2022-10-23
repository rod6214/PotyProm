#include "so.h"
#include "gpio.h"

extern unsigned int _estack;

__attribute__ ((section(".isr_vector")))
const DeviceVectors exception_table = {
    .pvStack = (void*) (&_estack),
    .pfnReset_Handler = Reset_Handler,
    .pfnSVC_Handler = SVC_Handler,
    .pfnSysTick_Handler = SysTick_Handler,
    .pfnHardFault_Handler = HardFault_Handler
};

void ___syscall(int code) 
{
    asm("mov r0, %0"::"r"(code));
    asm("svc 1");
}
