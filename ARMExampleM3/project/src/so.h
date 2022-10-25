
#ifndef _SO_
#define _SO_

#ifdef __cplusplus
 extern "C" {
#endif 
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#include <stm32f1xx.h>

#define CFGR_PLL_MULL(x) ((x & 0xfL) << RCC_CFGR_PLLMULL_Pos)
#define CFGR_MCO(x) ((x & 0xfL) << RCC_CFGR_MCO_Pos)
#define CFGR_PPRE2(x) ((x & 0xfL) << RCC_CFGR_PPRE2_Pos)
#define CFGR_PPRE1(x) ((x & 0xfL) << RCC_CFGR_PPRE1_Pos)
#define CFGR_HPRE(x) ((x & 0xfL) << RCC_CFGR_HPRE_Pos)
#define CFGR_SWS(x) ((x & 0x3L) << RCC_CFGR_SWS_Pos)
#define CFGR_SW(x) ((x & 0x3L) << RCC_CFGR_SW_Pos)
#define CFGR_ADCPRE(x) ((x & 0x3L) << RCC_CFGR_ADCPRE_Pos)

typedef void (*FUNC)(void);
typedef void (*FUNC_SVC)(int);

typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;
  
  /* Cortex-M handlers */
  FUNC pfnReset_Handler;
  FUNC pfnNMI_Handler;
  FUNC pfnHardFault_Handler;
  FUNC pfnMemManage_Handler;
  FUNC pfnBusFault_Handler;
  FUNC pfnUsageFault_Handler;
  FUNC pfnReserved1_Handler;
  FUNC pfnReserved2_Handler;
  FUNC pfnReserved3_Handler;
  FUNC pfnReserved4_Handler;
  FUNC pfnSVC_Handler;
  FUNC pfnDebugMon_Handler;
  FUNC pfnReserved5_Handler;
  FUNC pfnPendSV_Handler;
  FUNC pfnSysTick_Handler;

  /* Peripheral handlers */
  FUNC pfnWWDG_Handler;
  FUNC pfnPVD_Handler;
  FUNC pfnTAMPER_Handler;
  FUNC pfnRTC_Handler;
  FUNC pfnFLASH_Handler;
  FUNC pfnRCC_Handler;
  FUNC pfnEXTI0_IRQHandler;
  FUNC pfnEXTI1_IRQHandler;
  FUNC pfnEXTI2_IRQHandler;
  FUNC pfnEXTI3_IRQHandler;
  FUNC pfnEXTI4_IRQHandler;
  FUNC pfnDMA1_Channel1_IRQHandler;
  FUNC pfnDMA1_Channel2_IRQHandler;
  FUNC pfnDMA1_Channel3_IRQHandler;
  FUNC pfnDMA1_Channel4_IRQHandler;
  FUNC pfnDMA1_Channel5_IRQHandler;
  FUNC pfnDMA1_Channel6_IRQHandler;
  FUNC pfnDMA1_Channel7_IRQHandler;
  FUNC pfnADC1_2_IRQHandler;
  FUNC pfnCAN1_TX_IRQHandler;
  FUNC pfnCAN1_RX0_IRQHandler;
  FUNC pfnCAN1_RX1_IRQHandler;
  FUNC pfnCAN1_SCE_IRQHandler;
  FUNC pfnEXTI9_5_IRQHandler;
  FUNC pfnTIM1_BRK_IRQHandler;
  FUNC pfnTIM1_UP_IRQHandler;
  FUNC pfnTIM1_TRG_COM_IRQHandler;
  FUNC pfnTIM1_CC_IRQHandler;
  FUNC pfnTIM2_IRQHandler;
  FUNC pfnTIM3_IRQHandler;
  FUNC pfnTIM4_IRQHandler;
  FUNC pfnI2C1_EV_IRQHandler;
  FUNC pfnI2C1_ER_IRQHandler;
  FUNC pfnI2C2_EV_IRQHandler;
  FUNC pfnI2C2_ER_IRQHandler;
  FUNC pfnSPI1_IRQHandler;
  FUNC pfnSPI2_IRQHandler;
  FUNC pfnUSART1_IRQHandler;
  FUNC pfnUSART2_IRQHandler;
  FUNC pfnUSART3_IRQHandler;
  FUNC pfnEXTI15_10_IRQHandler;
  FUNC pfnRTC_Alarm_IRQHandler;
  FUNC pfnOTG_FS_WKUP_IRQHandler;
  FUNC pfnReserved6_Handler;
  FUNC pfnReserved7_Handler;
  FUNC pfnReserved8_Handler;
  FUNC pfnReserved9_Handler;
  FUNC pfnReserved10_Handler;
  FUNC pfnReserved11_Handler;
  FUNC pfnReserved12_Handler;
  FUNC pfnTIM5_IRQHandler;
  FUNC pfnSPI3_IRQHandler;
  FUNC pfnUART4_IRQHandler;
  FUNC pfnUART5_IRQHandler;
  FUNC pfnTIM6_IRQHandler;
  FUNC pfnTIM7_IRQHandler;
  FUNC pfnDMA2_Channel1_IRQHandler;
  FUNC pfnDMA2_Channel2_IRQHandler;
  FUNC pfnDMA2_Channel3_IRQHandler;
  FUNC pfnDMA2_Channel4_IRQHandler;
  FUNC pfnDMA2_Channel5_IRQHandler;
  FUNC pfnETH_IRQHandler;
  FUNC pfnETH_WKUP_IRQHandler;
  FUNC pfnCAN2_TX_IRQHandler;
  FUNC pfnCAN2_RX0_IRQHandler;
  FUNC pfnCAN2_RX1_IRQHandler;
  FUNC pfnCAN2_SCE_IRQHandler;
  FUNC pfnOTG_FS_IRQHandler;
} DeviceVectors;

#ifndef NULL
#define NULL (void*)0
#endif
#define ___AT(x) ((unsigned int*)x)

#define __START__  __attribute__ ((section(".so_start")))
#define __EXTERNAL__  __attribute__ ((section(".so_fn")))
#define __THUMB__  __attribute__((target("thumb")))

typedef void (*SubscribeCallback)();

typedef struct Subs {
int code;
SubscribeCallback callback;
} Subs_t;

extern void ___syscall(int code);
extern void add_subscriber(Subs_t subscriber);
extern void remove_subscriber(Subs_t subscriber);
extern void Reset_Handler(void);
extern void SVC_Handler();
extern void SysTick_Handler();
extern void RTC_Handler();
extern void reset_list();
extern void HardFault_Handler();
extern void CLOCK_start_default();
extern void CLOCK_enable_FMC();
extern void CLOCK_reset_FMC();
extern void CLOCK_enable_AHB1(uint32_t values);
extern void FMC_SDRAM_start_default();
extern void FMC_SDRAM_prepare_ports();
extern void BOOT_OperatingSystem(uint32_t address);
extern void enable_IRQn(IRQn_Type irq);
extern uint32_t CLOCK_GetTick();
extern void IRQ19_USB_HP_CAN_TX();
extern void IRQ20_USB_LP_CAN_RX0(); 
extern void IRQ42_USBWakeUp();
extern void CLOCK_Delay(uint32_t value);


#define SYSTICK_ID          1
#define SYSCALL_ID          2
#define RTC_ID              3
#define RTC_SECOND_ID       4
#define USB_HP_CAN_TX_ID    5
#define USB_LP_CAN_RX0_ID   6
#define USBWakeUp_ID        7

#define FALSE 0
#define TRUE 1

#define SO_ENTRY __attribute__ ((section(".entry")))

typedef void (*SubscriberHandler)(Subs_t subscriber);
typedef void (*SyscallHandler)(int code);

typedef struct 
{
    SyscallHandler syscall;
    SubscriberHandler add_subscriber;
    SubscriberHandler remove_subscriber;
} SO_Input_t;

#define CALL_OPERATING_SYSTEM(ptr) asm volatile ( \
        "mov r0, %0\n\t" \
        "ldr r1, =#0xD0000000\n\t" \
        "blx r1" \
        : \
        : "r"(&input))

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _SO_ */