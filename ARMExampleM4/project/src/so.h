
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

#define PIOA_ID (0x800U)
#define PIOB_ID (0x800U << 1)
#define PIOC_ID (0x800U << 2)
#define PIOD_ID (0x800U << 3)
#define PIOE_ID (0x800U << 4)
#define PIOF_ID (0x800U << 5)
#define P0 1
#define P1 (1 << 1)
#define P2 (1 << 2)
#define P3 (1 << 3)
#define P4 (1 << 4)
#define P5 (1 << 5)
#define P6 (1 << 6)
#define P7 (1 << 7)
#define P8 (1 << 8)
#define P9 (1 << 9)
#define P10 (1 << 10)
#define P11 (1 << 11)
#define P12 (1 << 12)
#define P13 (1 << 13)
#define P14 (1 << 14)
#define P15 (1 << 15)
#define P16 (1 << 16)
#define P17 (1 << 17)
#define P18 (1 << 18)
#define P19 (1 << 19)
#define P20 (1 << 20)
#define P21 (1 << 21)
#define P22 (1 << 22)
#define P23 (1 << 23)
#define P24 (1 << 24)
#define P25 (1 << 25)
#define P26 (1 << 26)
#define P27 (1 << 27)
#define P28 (1 << 28)
#define P29 (1 << 29)
#define P30 (1 << 30)
#define P31 (1 << 31)

#define PIO_PER_A (unsigned int)(0x400E0E00U)
#define PIO_PER_B (unsigned int)(PIO_PER_A + 0x200)
#define PIO_PER_C (unsigned int)(PIO_PER_B + 0x200)
#define PIO_PER_D (unsigned int)(PIO_PER_C + 0x200)
#define PIO_PER_E (unsigned int)(PIO_PER_D + 0x200)
#define PIO_PER_F (unsigned int)(PIO_PER_E + 0x200)
#define PIO_PDR_A (unsigned int)(0x400E0E04U)
#define PIO_PDR_B (unsigned int)(PIO_PDR_A + 0x200)
#define PIO_PDR_C (unsigned int)(PIO_PDR_B + 0x200)
#define PIO_PDR_D (unsigned int)(PIO_PDR_C + 0x200)
#define PIO_PDR_E (unsigned int)(PIO_PDR_D + 0x200)
#define PIO_PDR_F (unsigned int)(PIO_PDR_E + 0x200)
#define PIO_OER_A (unsigned int)(0x400E0E10U)
#define PIO_OER_B (unsigned int)(PIO_OER_A + 0x200)
#define PIO_OER_C (unsigned int)(PIO_OER_B + 0x200)
#define PIO_OER_D (unsigned int)(PIO_OER_C + 0x200)
#define PIO_OER_E (unsigned int)(PIO_OER_D + 0x200)
#define PIO_OER_F (unsigned int)(PIO_OER_E + 0x200)
#define PIO_SODR_A (unsigned int)(0x400E0E30U)
#define PIO_SODR_B (unsigned int)(PIO_SODR_A + 0x200)
#define PIO_SODR_C (unsigned int)(PIO_SODR_B + 0x200)
#define PIO_SODR_D (unsigned int)(PIO_SODR_C + 0x200)
#define PIO_SODR_E (unsigned int)(PIO_SODR_D + 0x200)
#define PIO_SODR_F (unsigned int)(PIO_SODR_E + 0x200)
#define PIO_CODR_A (unsigned int)(0x400E0E34U)
#define PIO_CODR_B (unsigned int)(PIO_CODR_A + 0x200)
#define PIO_CODR_C (unsigned int)(PIO_CODR_B + 0x200)
#define PIO_CODR_D (unsigned int)(PIO_CODR_C + 0x200)
#define PIO_CODR_E (unsigned int)(PIO_CODR_D + 0x200)
#define PIO_CODR_F (unsigned int)(PIO_CODR_E + 0x200)
#define PMC_PCER0 (unsigned int)(0x400E0610U)

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

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

typedef struct SysTick 
{
    __IOM uint32_t CTRL;
    __IOM uint32_t LOAD;
    __IOM uint32_t VAL;
    __IOM uint32_t CALIB;
} SysTick_t;

typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

#define SCB ((SCB_Type*)0xE000ED00UL)   /*!< SCB configuration struct */
#define SYSTICK ((SysTick_t*)0xE000E010UL)   /*!< SYSTICK configuration struct */

#define USGFAULTENA (1 << 18)
#define BUSFAULTENA (1 << 17)
#define MEMFAULTENA (1 << 16)
#define SVCALLPENDED (1 << 15)
#define BUSFAULTPENDED (1 << 14)
#define MEMFAULTPENDED (1 << 13)
#define USGFAULTPENDED (1 << 12)
#define SYSTICKACT (1 << 11)
#define PENDSVACT (1 << 10)
#define MONITORACT (1 << 8)
#define SVCALLACT (1 << 7)
#define USGFAULTACT (1 << 3)
#define BUSFAULTACT (1 << 2)
#define MEMFAULTACT (1 << 1)

#define SYSTICK_ID 10
#define SYSCALL_ID 1

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _SO_ */