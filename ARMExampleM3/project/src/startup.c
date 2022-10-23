#include "so.h"
#include "gpio.h"

extern unsigned int _estack;
void Default_Handler();
void RCC_Handler();

__attribute__ ((section(".isr_vector")))
const DeviceVectors exception_table = {
    .pvStack = (void*) (&_estack),
    .pfnReset_Handler = Reset_Handler,
    .pfnNMI_Handler = Default_Handler,
    .pfnHardFault_Handler = HardFault_Handler,
    .pfnMemManage_Handler = Default_Handler,
    .pfnBusFault_Handler = Default_Handler,
    .pfnUsageFault_Handler = Default_Handler,
    .pfnSVC_Handler = SVC_Handler,
    .pfnDebugMon_Handler = Default_Handler,
    .pfnPendSV_Handler = Default_Handler,
    .pfnSysTick_Handler = SysTick_Handler,

    // Peripherals
    .pfnWWDG_Handler = Default_Handler,
    .pfnPVD_Handler = Default_Handler,
    .pfnTAMPER_Handler = Default_Handler,
    .pfnRTC_Handler = Default_Handler,
    .pfnFLASH_Handler = Default_Handler,
    .pfnRCC_Handler = Default_Handler,
    .pfnEXTI0_IRQHandler = Default_Handler,
    .pfnEXTI1_IRQHandler = Default_Handler,
    .pfnEXTI2_IRQHandler = Default_Handler,
    .pfnEXTI3_IRQHandler = Default_Handler,
    .pfnEXTI4_IRQHandler = Default_Handler,
    .pfnDMA1_Channel1_IRQHandler = Default_Handler,
    .pfnDMA1_Channel2_IRQHandler = Default_Handler,
    .pfnDMA1_Channel3_IRQHandler = Default_Handler,
    .pfnDMA1_Channel4_IRQHandler = Default_Handler,
    .pfnDMA1_Channel5_IRQHandler = Default_Handler,
    .pfnDMA1_Channel6_IRQHandler = Default_Handler,
    .pfnDMA1_Channel7_IRQHandler = Default_Handler,
    .pfnADC1_2_IRQHandler = Default_Handler,
    .pfnCAN1_TX_IRQHandler = Default_Handler,
    .pfnCAN1_RX0_IRQHandler = Default_Handler,
    .pfnCAN1_RX1_IRQHandler = Default_Handler,
    .pfnCAN1_SCE_IRQHandler = Default_Handler,
    .pfnEXTI9_5_IRQHandler = Default_Handler,
    .pfnTIM1_BRK_IRQHandler = Default_Handler,
    .pfnTIM1_UP_IRQHandler = Default_Handler,
    .pfnTIM1_TRG_COM_IRQHandler = Default_Handler,
    .pfnTIM1_CC_IRQHandler = Default_Handler,
    .pfnTIM2_IRQHandler = Default_Handler,
    .pfnTIM3_IRQHandler = Default_Handler,
    .pfnTIM4_IRQHandler = Default_Handler,
    .pfnI2C1_EV_IRQHandler = Default_Handler,
    .pfnI2C1_ER_IRQHandler = Default_Handler,
    .pfnI2C2_EV_IRQHandler = Default_Handler,
    .pfnI2C2_ER_IRQHandler = Default_Handler,
    .pfnSPI1_IRQHandler = Default_Handler,
    .pfnSPI2_IRQHandler = Default_Handler,
    .pfnUSART1_IRQHandler = Default_Handler,
    .pfnUSART2_IRQHandler = Default_Handler,
    .pfnUSART3_IRQHandler = Default_Handler,
    .pfnEXTI15_10_IRQHandler = Default_Handler,
    .pfnRTC_Alarm_IRQHandler = Default_Handler,
    .pfnOTG_FS_WKUP_IRQHandler = Default_Handler,
    .pfnReserved6_Handler = Default_Handler,
    .pfnReserved7_Handler = Default_Handler,
    .pfnReserved8_Handler = Default_Handler,
    .pfnReserved9_Handler = Default_Handler,
    .pfnReserved10_Handler = Default_Handler,
    .pfnReserved11_Handler = Default_Handler,
    .pfnReserved12_Handler = Default_Handler,
    .pfnTIM5_IRQHandler = Default_Handler,
    .pfnSPI3_IRQHandler = Default_Handler,
    .pfnUART4_IRQHandler = Default_Handler,
    .pfnUART5_IRQHandler = Default_Handler,
    .pfnTIM6_IRQHandler = Default_Handler,
    .pfnTIM7_IRQHandler = Default_Handler,
    .pfnDMA2_Channel1_IRQHandler = Default_Handler,
    .pfnDMA2_Channel2_IRQHandler = Default_Handler,
    .pfnDMA2_Channel3_IRQHandler = Default_Handler,
    .pfnDMA2_Channel4_IRQHandler = Default_Handler,
    .pfnDMA2_Channel5_IRQHandler = Default_Handler,
    .pfnETH_IRQHandler = Default_Handler,
    .pfnETH_WKUP_IRQHandler = Default_Handler,
    .pfnCAN2_TX_IRQHandler = Default_Handler,
    .pfnCAN2_RX0_IRQHandler = Default_Handler,
    .pfnCAN2_RX1_IRQHandler = Default_Handler,
    .pfnCAN2_SCE_IRQHandler = Default_Handler,
    .pfnOTG_FS_IRQHandler = Default_Handler,
};

void RCC_Handler() 
{

}

void Default_Handler() 
{
    int *r = (int*)(0x20000000);
    *r = 9;
}

void ___syscall(int code) 
{
    asm("mov r0, %0"::"r"(code));
    asm("svc 1");
}
