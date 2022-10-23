
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
  FUNC_SVC pfnSVC_Handler;
  FUNC pfnDebugMon_Handler;
  FUNC pfnReserved5_Handler;
  FUNC pfnPendSV_Handler;
  FUNC pfnSysTick_Handler;

  /* Peripheral handlers */
  FUNC pfnSUPC_Handler;   /*  0 Supply Controller */
  FUNC pfnRSTC_Handler;   /*  1 Reset Controller */
  FUNC pfnRTC_Handler;    /*  2 Real Time Clock */
  FUNC pfnRTT_Handler;    /*  3 Real Time Timer */
  FUNC pfnWDT_Handler;    /*  4 Watchdog Timer */
  FUNC pfnPMC_Handler;    /*  5 Power Management Controller */
  FUNC pfnEFC0_Handler;   /*  6 Enhanced Flash Controller 0 */
  FUNC pfnEFC1_Handler;   /*  7 Enhanced Flash Controller 1 */
  FUNC pfnUART_Handler;   /*  8 Universal Asynchronous Receiver Transceiver */
  FUNC pvReserved9;
  FUNC pvReserved10;
  FUNC pfnPIOA_Handler;   /* 11 Parallel I/O Controller A, */
  FUNC pfnPIOB_Handler;   /* 12 Parallel I/O Controller B */
  FUNC pvReserved13;
  FUNC pvReserved14;
  FUNC pvReserved15;
  FUNC pvReserved16;
  FUNC pfnUSART0_Handler; /* 17 USART 0 */
  FUNC pfnUSART1_Handler; /* 18 USART 1 */
  FUNC pfnUSART2_Handler; /* 19 USART 2 */
  FUNC pvReserved20;
  FUNC pfnHSMCI_Handler;  /* 21 Multimedia Card Interface */
  FUNC pfnTWI0_Handler;   /* 22 Two-Wire Interface 0 */
  FUNC pfnTWI1_Handler;   /* 23 Two-Wire Interface 1 */
  FUNC pfnSPI0_Handler;   /* 24 Serial Peripheral Interface */
  FUNC pvReserved25;
  FUNC pfnSSC_Handler;    /* 26 Synchronous Serial Controller */
  FUNC pfnTC0_Handler;    /* 27 Timer Counter 0 */
  FUNC pfnTC1_Handler;    /* 28 Timer Counter 1 */
  FUNC pfnTC2_Handler;    /* 29 Timer Counter 2 */
  FUNC pfnTC3_Handler;    /* 30 Timer Counter 3 */
  FUNC pfnTC4_Handler;    /* 31 Timer Counter 4 */
  FUNC pfnTC5_Handler;    /* 32 Timer Counter 5 */
  FUNC pvReserved33;
  FUNC pvReserved34;
  FUNC pvReserved35;
  FUNC pfnPWM_Handler;    /* 36 Pulse Width Modulation Controller */
  FUNC pfnADC_Handler;    /* 37 ADC Controller */
  FUNC pfnDACC_Handler;   /* 38 DAC Controller */
  FUNC pfnDMAC_Handler;   /* 39 DMA Controller */
  FUNC pfnUOTGHS_Handler; /* 40 USB OTG High Speed */
  FUNC pfnTRNG_Handler;   /* 41 True Random Number Generator */
  FUNC pfnEMAC_Handler;   /* 42 Ethernet MAC */
  FUNC pfnCAN0_Handler;   /* 43 CAN Controller 0 */
  FUNC pfnCAN1_Handler;   /* 44 CAN Controller 1 */
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
extern void SVC_Handler(int code);
extern void SysTick_Handler();
extern void reset_list();
extern void HardFault_Handler();
extern void CLOCK_start_default();
extern void CLOCK_enable_FMC();
extern void CLOCK_reset_FMC();
extern void CLOCK_enable_AHB1(uint32_t values);
extern void FMC_SDRAM_start_default();
extern void FMC_SDRAM_prepare_ports();
extern void BOOT_OperatingSystem(uint32_t address);

#define SYSTICK_ID 10
#define SYSCALL_ID 1

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