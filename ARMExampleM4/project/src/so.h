
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

#define RCC_BASE 0x40023800UL
#define FMC_BASE 0xA0000000UL
#define SDRAM_CONTROLLER (FMC_BASE + 0x140)
#define SDRAM_BASE 0xD0000000
#define SDRAM_SIZE 0x00000200
#define GPIOA_BASE 0x40020000 
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOD_BASE 0x40020C00
#define GPIOE_BASE 0x40021000
#define GPIOF_BASE 0x40021400
#define GPIOG_BASE 0x40021800
#define GPIOH_BASE 0x40021C00
#define GPIOI_BASE 0x40022000
#define GPIOJ_BASE 0x40022400
#define GPIOK_BASE 0x40022800

#define LOW_SPEED       0
#define MEDIUM_SPEED    1
#define FAST_SPEED      2
#define HIGH_SPEED      3

#define OSPEEDR0(x)     ((x & 3UL) << 0*2)
#define OSPEEDR1(x)     ((x & 3UL) << 1*2)
#define OSPEEDR2(x)     ((x & 3UL) << 2*2)
#define OSPEEDR3(x)     ((x & 3UL) << 3*2)
#define OSPEEDR4(x)     ((x & 3UL) << 4*2)
#define OSPEEDR5(x)     ((x & 3UL) << 5*2)
#define OSPEEDR6(x)     ((x & 3UL) << 6*2)
#define OSPEEDR7(x)     ((x & 3UL) << 7*2)
#define OSPEEDR8(x)     ((x & 3UL) << 8*2)
#define OSPEEDR9(x)     ((x & 3UL) << 9*2)
#define OSPEEDR10(x)    ((x & 3UL) << 10*2)
#define OSPEEDR11(x)    ((x & 3UL) << 11*2)
#define OSPEEDR12(x)    ((x & 3UL) << 12*2)
#define OSPEEDR13(x)    ((x & 3UL) << 13*2)
#define OSPEEDR14(x)    ((x & 3UL) << 14*2)
#define OSPEEDR15(x)    ((x & 3UL) << 15*2)

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



typedef struct 
{
    __IOM uint32_t CR;
    __IOM uint32_t PLLCFGR;
    __IOM uint32_t CFGR;
    __IOM uint32_t CIR;
    __IOM uint32_t AHB1RSTR;
    __IOM uint32_t AHB2RSTR;
    __IOM uint32_t AHB3RSTR;
          uint32_t RESERVED0;
    __IOM uint32_t APB1RSTR;
    __IOM uint32_t APB2RSTR;
          uint32_t RESERVED1[2];
    __IOM uint32_t AHB1ENR;
    __IOM uint32_t AHB2ENR;
    __IOM uint32_t AHB3ENR;
          uint32_t RESERVED2;
    __IOM uint32_t APB1ENR;
    __IOM uint32_t APB2ENR;
          uint32_t RESERVED3[2];
    __IOM uint32_t AHB1LPENR;
    __IOM uint32_t AHB2LPENR;
    __IOM uint32_t AHB3LPENR;
          uint32_t RESERVED4;
    __IOM uint32_t APB1LPENR;
    __IOM uint32_t APB2LPENR;
          uint32_t RESERVED5[2];
    __IOM uint32_t BDCR;
    __IOM uint32_t CSR;
          uint32_t RESERVED6[2];
    __IOM uint32_t SSCGR;
    __IOM uint32_t PLLI2SCFGR;
    __IOM uint32_t PLLSAICFGR;
    __IOM uint32_t DCKCFGR;
}
RCC_t;

typedef struct 
{
    __IOM uint32_t SDCR_1;
    __IOM uint32_t SDCR_2;
    __IOM uint32_t SDTR1;
    __IOM uint32_t SDTR2;
    __IOM uint32_t SDCMR;
    __IOM uint32_t SDRTR;
    __IM uint32_t SDSR;
}
SDRAM_C_t;

typedef struct 
{
    __IOM uint32_t GPIOx_MODER;
    __IOM uint32_t GPIOx_OTYPER;
    __IOM uint32_t GPIOx_OSPEEDR;
    __IOM uint32_t GPIOx_PUPDR;
    __IOM uint32_t GPIOx_IDR;
    __IOM uint32_t GPIOx_ODR;
    __IOM uint32_t GPIOx_BSRR;
    __IOM uint32_t GPIOx_LCKR;
    __IOM uint32_t GPIOx_AFRL;
    __IOM uint32_t GPIOx_AFRH;
}
GPIO_t;

#define FMC_SDCR1_SDCLK_Pos         (10U)                                      
#define FMC_SDCR1_SDCLK_Msk         (0x3UL << FMC_SDCR1_SDCLK_Pos)              /*!< 0x00000C00 */
#define FMC_SDCR1_SDCLK             FMC_SDCR1_SDCLK_Msk                        /*!<SDRAM clock configuration */
#define FMC_SDCR1_SDCLK_0           (0x1UL << FMC_SDCR1_SDCLK_Pos)              /*!< 0x00000400 */
#define FMC_SDCR1_SDCLK_1           (0x2UL << FMC_SDCR1_SDCLK_Pos)              /*!< 0x00000800 */

#define FMC_SDCR1_RBURST_Pos        (12U)                                      
#define FMC_SDCR1_RBURST_Msk        (0x1UL << FMC_SDCR1_RBURST_Pos)             /*!< 0x00001000 */
#define FMC_SDCR1_RBURST            FMC_SDCR1_RBURST_Msk                       /*!<Read burst */

#define FMC_SDCR1_RPIPE_Pos         (13U)                                      
#define FMC_SDCR1_RPIPE_Msk         (0x3UL << FMC_SDCR1_RPIPE_Pos)              /*!< 0x00006000 */
#define FMC_SDCR1_RPIPE             FMC_SDCR1_RPIPE_Msk                        /*!<Write protection */
#define FMC_SDCR1_RPIPE_0           (0x1UL << FMC_SDCR1_RPIPE_Pos)              /*!< 0x00002000 */
#define FMC_SDCR1_RPIPE_1           (0x2UL << FMC_SDCR1_RPIPE_Pos)              /*!< 0x00004000 */

#define FMC_SDCR1_NR_Pos            (2U)                                       
#define FMC_SDCR1_NR_Msk            (0x3UL << FMC_SDCR1_NR_Pos)                 /*!< 0x0000000C */
#define FMC_SDCR1_NR                FMC_SDCR1_NR_Msk                           /*!<NR[1:0] bits (Number of row bits) */
#define FMC_SDCR1_NR_0              (0x1UL << FMC_SDCR1_NR_Pos)                 /*!< 0x00000004 */
#define FMC_SDCR1_NR_1              (0x2UL << FMC_SDCR1_NR_Pos)                 /*!< 0x00000008 */

#define FMC_SDCR1_MWID_Pos          (4U)                                       
#define FMC_SDCR1_MWID_Msk          (0x3UL << FMC_SDCR1_MWID_Pos)               /*!< 0x00000030 */
#define FMC_SDCR1_MWID              FMC_SDCR1_MWID_Msk                         /*!<NR[1:0] bits (Number of row bits) */
#define FMC_SDCR1_MWID_0            (0x1UL << FMC_SDCR1_MWID_Pos)               /*!< 0x00000010 */
#define FMC_SDCR1_MWID_1            (0x2UL << FMC_SDCR1_MWID_Pos)               /*!< 0x00000020 */

#define FMC_SDCR1_NB_Pos            (6U)                                       
#define FMC_SDCR1_NB_Msk            (0x1UL << FMC_SDCR1_NB_Pos)                 /*!< 0x00000040 */
#define FMC_SDCR1_NB                FMC_SDCR1_NB_Msk                           /*!<Number of internal bank */

#define FMC_SDCR1_CAS_Pos           (7U)                                       
#define FMC_SDCR1_CAS_Msk           (0x3UL << FMC_SDCR1_CAS_Pos)                /*!< 0x00000180 */
#define FMC_SDCR1_CAS               FMC_SDCR1_CAS_Msk                          /*!<CAS[1:0] bits (CAS latency) */
#define FMC_SDCR1_CAS_0             (0x1UL << FMC_SDCR1_CAS_Pos)                /*!< 0x00000080 */
#define FMC_SDCR1_CAS_1             (0x2UL << FMC_SDCR1_CAS_Pos)                /*!< 0x00000100 */

#define FMC_SDSR_BUSY_Pos           (5U)                                       
#define FMC_SDSR_BUSY_Msk           (0x1UL << FMC_SDSR_BUSY_Pos)                /*!< 0x00000020 */
#define FMC_SDSR_BUSY               FMC_SDSR_BUSY_Msk                          /*!<Busy status */

#define RCC_AHB1ENR_GPIOAEN_Pos            (0U)                                
#define RCC_AHB1ENR_GPIOAEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOAEN_Pos)   /*!< 0x00000001 */
#define RCC_AHB1ENR_GPIOAEN                RCC_AHB1ENR_GPIOAEN_Msk             
#define RCC_AHB1ENR_GPIOBEN_Pos            (1U)                                
#define RCC_AHB1ENR_GPIOBEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOBEN_Pos)   /*!< 0x00000002 */
#define RCC_AHB1ENR_GPIOBEN                RCC_AHB1ENR_GPIOBEN_Msk             
#define RCC_AHB1ENR_GPIOCEN_Pos            (2U)                                
#define RCC_AHB1ENR_GPIOCEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOCEN_Pos)   /*!< 0x00000004 */
#define RCC_AHB1ENR_GPIOCEN                RCC_AHB1ENR_GPIOCEN_Msk             
#define RCC_AHB1ENR_GPIODEN_Pos            (3U)                                
#define RCC_AHB1ENR_GPIODEN_Msk            (0x1UL << RCC_AHB1ENR_GPIODEN_Pos)   /*!< 0x00000008 */
#define RCC_AHB1ENR_GPIODEN                RCC_AHB1ENR_GPIODEN_Msk             
#define RCC_AHB1ENR_GPIOEEN_Pos            (4U)                                
#define RCC_AHB1ENR_GPIOEEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOEEN_Pos)   /*!< 0x00000010 */
#define RCC_AHB1ENR_GPIOEEN                RCC_AHB1ENR_GPIOEEN_Msk             
#define RCC_AHB1ENR_GPIOFEN_Pos            (5U)                                
#define RCC_AHB1ENR_GPIOFEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOFEN_Pos)   /*!< 0x00000020 */
#define RCC_AHB1ENR_GPIOFEN                RCC_AHB1ENR_GPIOFEN_Msk             
#define RCC_AHB1ENR_GPIOGEN_Pos            (6U)                                
#define RCC_AHB1ENR_GPIOGEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOGEN_Pos)   /*!< 0x00000040 */
#define RCC_AHB1ENR_GPIOGEN                RCC_AHB1ENR_GPIOGEN_Msk             
#define RCC_AHB1ENR_GPIOHEN_Pos            (7U)                                
#define RCC_AHB1ENR_GPIOHEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOHEN_Pos)   /*!< 0x00000080 */
#define RCC_AHB1ENR_GPIOHEN                RCC_AHB1ENR_GPIOHEN_Msk             
#define RCC_AHB1ENR_GPIOIEN_Pos            (8U)                                
#define RCC_AHB1ENR_GPIOIEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOIEN_Pos)   /*!< 0x00000100 */
#define RCC_AHB1ENR_GPIOIEN                RCC_AHB1ENR_GPIOIEN_Msk             
#define RCC_AHB1ENR_GPIOJEN_Pos            (9U)                                
#define RCC_AHB1ENR_GPIOJEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOJEN_Pos)   /*!< 0x00000200 */
#define RCC_AHB1ENR_GPIOJEN                RCC_AHB1ENR_GPIOJEN_Msk             
#define RCC_AHB1ENR_GPIOKEN_Pos            (10U)                               
#define RCC_AHB1ENR_GPIOKEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOKEN_Pos)   /*!< 0x00000400 */
#define RCC_AHB1ENR_GPIOKEN                RCC_AHB1ENR_GPIOKEN_Msk             
#define RCC_AHB1ENR_CRCEN_Pos              (12U)                               
#define RCC_AHB1ENR_CRCEN_Msk              (0x1UL << RCC_AHB1ENR_CRCEN_Pos)     /*!< 0x00001000 */
#define RCC_AHB1ENR_CRCEN                  RCC_AHB1ENR_CRCEN_Msk               
#define RCC_AHB1ENR_BKPSRAMEN_Pos          (18U)                               
#define RCC_AHB1ENR_BKPSRAMEN_Msk          (0x1UL << RCC_AHB1ENR_BKPSRAMEN_Pos) /*!< 0x00040000 */
#define RCC_AHB1ENR_BKPSRAMEN              RCC_AHB1ENR_BKPSRAMEN_Msk           
#define RCC_AHB1ENR_CCMDATARAMEN_Pos       (20U)                               
#define RCC_AHB1ENR_CCMDATARAMEN_Msk       (0x1UL << RCC_AHB1ENR_CCMDATARAMEN_Pos) /*!< 0x00100000 */
#define RCC_AHB1ENR_CCMDATARAMEN           RCC_AHB1ENR_CCMDATARAMEN_Msk        
#define RCC_AHB1ENR_DMA1EN_Pos             (21U)                               
#define RCC_AHB1ENR_DMA1EN_Msk             (0x1UL << RCC_AHB1ENR_DMA1EN_Pos)    /*!< 0x00200000 */
#define RCC_AHB1ENR_DMA1EN                 RCC_AHB1ENR_DMA1EN_Msk              
#define RCC_AHB1ENR_DMA2EN_Pos             (22U)                               
#define RCC_AHB1ENR_DMA2EN_Msk             (0x1UL << RCC_AHB1ENR_DMA2EN_Pos)    /*!< 0x00400000 */
#define RCC_AHB1ENR_DMA2EN                 RCC_AHB1ENR_DMA2EN_Msk              
#define RCC_AHB1ENR_DMA2DEN_Pos            (23U)                               
#define RCC_AHB1ENR_DMA2DEN_Msk            (0x1UL << RCC_AHB1ENR_DMA2DEN_Pos)   /*!< 0x00800000 */
#define RCC_AHB1ENR_DMA2DEN                RCC_AHB1ENR_DMA2DEN_Msk             
#define RCC_AHB1ENR_ETHMACEN_Pos           (25U)                               
#define RCC_AHB1ENR_ETHMACEN_Msk           (0x1UL << RCC_AHB1ENR_ETHMACEN_Pos)  /*!< 0x02000000 */
#define RCC_AHB1ENR_ETHMACEN               RCC_AHB1ENR_ETHMACEN_Msk            
#define RCC_AHB1ENR_ETHMACTXEN_Pos         (26U)                               
#define RCC_AHB1ENR_ETHMACTXEN_Msk         (0x1UL << RCC_AHB1ENR_ETHMACTXEN_Pos) /*!< 0x04000000 */
#define RCC_AHB1ENR_ETHMACTXEN             RCC_AHB1ENR_ETHMACTXEN_Msk          
#define RCC_AHB1ENR_ETHMACRXEN_Pos         (27U)                               
#define RCC_AHB1ENR_ETHMACRXEN_Msk         (0x1UL << RCC_AHB1ENR_ETHMACRXEN_Pos) /*!< 0x08000000 */
#define RCC_AHB1ENR_ETHMACRXEN             RCC_AHB1ENR_ETHMACRXEN_Msk          
#define RCC_AHB1ENR_ETHMACPTPEN_Pos        (28U)                               
#define RCC_AHB1ENR_ETHMACPTPEN_Msk        (0x1UL << RCC_AHB1ENR_ETHMACPTPEN_Pos) /*!< 0x10000000 */
#define RCC_AHB1ENR_ETHMACPTPEN            RCC_AHB1ENR_ETHMACPTPEN_Msk         
#define RCC_AHB1ENR_OTGHSEN_Pos            (29U)                               
#define RCC_AHB1ENR_OTGHSEN_Msk            (0x1UL << RCC_AHB1ENR_OTGHSEN_Pos)   /*!< 0x20000000 */
#define RCC_AHB1ENR_OTGHSEN                RCC_AHB1ENR_OTGHSEN_Msk             
#define RCC_AHB1ENR_OTGHSULPIEN_Pos        (30U)                               
#define RCC_AHB1ENR_OTGHSULPIEN_Msk        (0x1UL << RCC_AHB1ENR_OTGHSULPIEN_Pos) /*!< 0x40000000 */
#define RCC_AHB1ENR_OTGHSULPIEN            RCC_AHB1ENR_OTGHSULPIEN_Msk     

#define SCB ((SCB_Type*)0xE000ED00UL)   /*!< SCB configuration struct */
#define SYSTICK ((SysTick_t*)0xE000E010UL)   /*!< SYSTICK configuration struct */
#define RCC ((RCC_t*)0x40023800UL)   /*!< SYSTICK configuration struct */
#define SDRAMC (SDRAM_C_t*)SDRAM_CONTROLLER
#define GPIOA ((GPIO_t*)GPIOA_BASE)
#define GPIOB ((GPIO_t*)GPIOB_BASE)
#define GPIOC ((GPIO_t*)GPIOC_BASE)
#define GPIOD ((GPIO_t*)GPIOD_BASE)
#define GPIOE ((GPIO_t*)GPIOE_BASE)
#define GPIOF ((GPIO_t*)GPIOF_BASE)
#define GPIOG ((GPIO_t*)GPIOG_BASE)
#define GPIOH ((GPIO_t*)GPIOH_BASE)
#define GPIOI ((GPIO_t*)GPIOI_BASE)
#define GPIOJ ((GPIO_t*)GPIOJ_BASE)
#define GPIOK ((GPIO_t*)GPIOK_BASE)

#define SELECT_BIT(x) (1 << x)

#define GPIOA_EN        SELECT_BIT(0)
#define GPIOB_EN        SELECT_BIT(1)
#define GPIOC_EN        SELECT_BIT(2)
#define GPIOD_EN        SELECT_BIT(3)
#define GPIOE_EN        SELECT_BIT(4)
#define GPIOF_EN        SELECT_BIT(5)
#define GPIOG_EN        SELECT_BIT(6)
#define GPIOH_EN        SELECT_BIT(7)
#define GPIOI_EN        SELECT_BIT(8)
#define GPIOJ_EN        SELECT_BIT(9)
#define GPIOK_EN        SELECT_BIT(10)

#define PLLSAIRDY      SELECT_BIT(29)
#define PLLISAION      SELECT_BIT(28)
#define PLLI2SRDY      SELECT_BIT(27)
#define PLLI2SON       SELECT_BIT(26)
#define PLLRDY         SELECT_BIT(25)
#define PLLON          SELECT_BIT(24)
#define CSSON          SELECT_BIT(19)
#define HSEBYP         SELECT_BIT(18)
#define HSERDY         SELECT_BIT(17)
#define HSEON          SELECT_BIT(16)
#define HSICAL7        SELECT_BIT(15)
#define HSICAL6        SELECT_BIT(14)
#define HSICAL5        SELECT_BIT(13)
#define HSICAL4        SELECT_BIT(12)
#define HSICAL3        SELECT_BIT(11)
#define HSICAL2        SELECT_BIT(10)
#define HSICAL1        SELECT_BIT(9)
#define HSICAL0        SELECT_BIT(8)
#define HSITRIM4       SELECT_BIT(7)
#define HSITRIM3       SELECT_BIT(6)
#define HSITRIM2       SELECT_BIT(5)
#define HSITRIM1       SELECT_BIT(4)
#define HSITRIM0       SELECT_BIT(3)
#define HSIRDY         SELECT_BIT(1)
#define HSION          SELECT_BIT(0)

#define DACEN           SELECT_BIT(29)
#define PWREN           SELECT_BIT(28)
#define CAN2EN          SELECT_BIT(26)
#define CAN1EN          SELECT_BIT(25)
#define I2C3EN          SELECT_BIT(23)
#define I2C2EN          SELECT_BIT(22)
#define I2C1EN          SELECT_BIT(21)
#define UART5EN         SELECT_BIT(20)
#define UART4EN         SELECT_BIT(19)
#define USART3EN        SELECT_BIT(18)
#define USART2EN        SELECT_BIT(17)
#define SPI3EN          SELECT_BIT(15)
#define SPI2EN          SELECT_BIT(14)
#define WWDGEN          SELECT_BIT(11)
#define TIM14EN         SELECT_BIT(8)
#define TIM13EN         SELECT_BIT(7)
#define TIM12EN         SELECT_BIT(6)
#define TIM7EN          SELECT_BIT(5)
#define TIM6EN          SELECT_BIT(4)
#define TIM5EN          SELECT_BIT(3)
#define TIM4EN          SELECT_BIT(2)
#define TIM3EN          SELECT_BIT(1)
#define TIM2EN          SELECT_BIT(0)
// 
#define PLLQ3           SELECT_BIT(27)
#define PLLQ2           SELECT_BIT(26)
#define PLLQ1           SELECT_BIT(25)
#define PLLQ0           SELECT_BIT(24)
#define PLLSRC          SELECT_BIT(22)
#define PLLP1           SELECT_BIT(17)
#define PLLP0           SELECT_BIT(16)
#define PLLN8           SELECT_BIT(14)
#define PLLN7           SELECT_BIT(13)
#define PLLN6           SELECT_BIT(12)
#define PLLN5           SELECT_BIT(11)
#define PLLN4           SELECT_BIT(10)
#define PLLN3           SELECT_BIT(9)
#define PLLN2           SELECT_BIT(8)
#define PLLN1           SELECT_BIT(7)
#define PLLN0           SELECT_BIT(6)
#define PLLM5           SELECT_BIT(5)
#define PLLM4           SELECT_BIT(4)
#define PLLM3           SELECT_BIT(3)
#define PLLM2           SELECT_BIT(2)
#define PLLM1           SELECT_BIT(1)
#define PLLM0           SELECT_BIT(0)

#define PLLP(x)         ((x & 3) << 16)
#define PLLN(x)         ((x & 0x1ff) << 6)
#define PLLM(x)         ((x & 0x1f) << 0)
#define MCO2(x)         (uint32_t)((x & 3) << 30)
#define HPRE(x)         (uint32_t)((x & 0xf) << 4)
#define MCO2PRE(x)      (uint32_t)((x & 0x7) << 27)
// 
#define MCO21           SELECT_BIT(31)
#define MCO20           SELECT_BIT(30)
#define MCO2PRE2        SELECT_BIT(29)
#define MCO2PRE1        SELECT_BIT(28)
#define MCO2PRE0        SELECT_BIT(27)
#define MCO1PRE2        SELECT_BIT(26)
#define MCO1PRE1        SELECT_BIT(25)
#define MCO1PRE0        SELECT_BIT(24)
#define I2SSRC          SELECT_BIT(23)
#define MC011           SELECT_BIT(22)
#define MCO10           SELECT_BIT(21)
#define RTCPRE4         SELECT_BIT(20)
#define RTCPRE3         SELECT_BIT(19)
#define RTCPRE2         SELECT_BIT(18)
#define RTCPRE1         SELECT_BIT(17)
#define RTCPRE0         SELECT_BIT(16)
#define PPRE22          SELECT_BIT(15)
#define PPRE21          SELECT_BIT(14)
#define PPRE20          SELECT_BIT(13)
#define PPRE12          SELECT_BIT(12)
#define PPRE11          SELECT_BIT(11)
#define PPRE10          SELECT_BIT(10)
#define HPRE3           SELECT_BIT(7)
#define HPRE2           SELECT_BIT(6)
#define HPRE1           SELECT_BIT(5)
#define HPRE0           SELECT_BIT(4)
#define SWS1            SELECT_BIT(3)
#define SWS0            SELECT_BIT(2)
#define SW1             SELECT_BIT(1)
#define SW0             SELECT_BIT(0)

#define FMCEN           SELECT_BIT(0)
#define FMCRST          SELECT_BIT(0)

//
#define CCLKEN          SELECT_BIT(20)
#define CBURSTRW        SELECT_BIT(19)
#define ASYNCWAIT       SELECT_BIT(15)
#define EXTMOD          SELECT_BIT(14)
#define WAITEN          SELECT_BIT(13)
#define WREN            SELECT_BIT(12)
#define WAITCFG         SELECT_BIT(11)
#define WAITPOL         SELECT_BIT(9)
#define BURSTEN         SELECT_BIT(8)
#define FACCEN          SELECT_BIT(6)
#define MWID(x)         ((x & 3) << 4)
#define MTYP(x)         ((x & 3) << 2)
#define MUXEN           SELECT_BIT(1)
#define MBKEN           SELECT_BIT(0)
//
#define ACCMOD(x)       ((x & 3) << 28)
#define DATLAT(x)       ((x & 0xf) << 24)
#define CLKDIV(x)       ((x & 0xf) <<20)
#define BUSTURN(x)      ((x & 0xf) << 16)
#define DATAST(x)       ((x & 0xff) << 8)
#define ADDHLD(x)       ((x & 0xf) << 4)
#define ADDSET(x)       ((x & 0xf) <<0)
// 
#define FEMPT           SELECT_BIT(6)
#define IFEN            SELECT_BIT(5)
#define ILEN            SELECT_BIT(4)
#define IREN            SELECT_BIT(3)
#define IFS             SELECT_BIT(2)
#define ILS             SELECT_BIT(1)
#define IRS             SELECT_BIT(0)
// 
#define ECCPS(x)        ((x & 7) << 17)
#define TAR(x)          ((x & 0xf) << 13)
#define TCLR(x)         ((x & 0xf) << 9)
#define ECCEN           SELECT_BIT(6)
#define PWID(x)         ((x & 3) << 4)
#define PTYP            SELECT_BIT(3)
#define PBKEN           SELECT_BIT(2)
#define PWAITEN         SELECT_BIT(1)
// 
#define MEMHIZ(x)       ((x & 0xffU) << 24)
#define MEMHOLD(x)      ((x & 0xffU) << 16)
#define MEMWAIT(x)      ((x & 0xffU) << 8)
#define MEMSET(x)       ((x & 0xffU) << 0)
//
#define ATTHIZ(x)       ((x & 0xffU) << 24)
#define ATTHOLD(x)      ((x & 0xffU) << 16)
#define ATTWAIT(x)      ((x & 0xffU) << 8)
#define ATTSET(x)       ((x & 0xffU) << 0)
//
#define IOHIZ(x)        ((x & 0xffU) << 24)
#define IOHOLD(x)       ((x & 0xffU) << 16)
#define IOWAIT(x)       ((x & 0xffU) << 8)
#define IOSET(x)        ((x & 0xffU) << 0)
//
#define RPIPE(x)        ((x & 3U) << 13)
#define RBURST          SELECT_BIT(12)
#define CLK(x)          ((x & 3U) << 10)
#define WP              SELECT_BIT(9)
#define CAS(x)          ((x & 3U) << 7) 
#define NB              SELECT_BIT(6)
#define NR(x)           ((x & 3U) << 2)
#define NC(x)           ((x & 3U) << 0)
//
#define TRCD(x)         ((x & 0xfU) << 24)
#define TRP(x)          ((x & 0xfU) << 20)
#define TWR(x)          ((x & 0xfU) << 16)
#define TRC(x)          ((x & 0xfU) << 12)
#define TRAS(x)         ((x & 0xfU) << 8)
#define TXSR(x)         ((x & 0xfU) << 4)
#define TMRD(x)         ((x & 0xfU) << 0)
//
#define MRD(x)          ((x & 0x1fff) << 9)
#define NRFS(x)         ((x & 0xf) << 5)
#define CTB1            SELECT_BIT(4)
#define CTB2            SELECT_BIT(3)
#define MODE(x)         ((x & 0xf) << 0)
//
#define REIE            SELECT_BIT(14)
#define COUNT(x)        ((x & 0x1fff) << 1)
#define CRE             SELECT_BIT(0)
//
#define BUSY            SELECT_BIT(10)
#define MODES2(x)       ((x & 3) << 3)
#define MODES1(x)       ((x & 3) << 1)
#define RE              SELECT_BIT(0)

#define MODER15(x)      ((x & 3UL) << 2*15)
#define MODER14(x)      ((x & 3UL) << 2*14)
#define MODER13(x)      ((x & 3UL) << 2*13)
#define MODER12(x)      ((x & 3UL) << 2*12)
#define MODER11(x)      ((x & 3UL) << 2*11)
#define MODER10(x)      ((x & 3UL) << 2*10)
#define MODER9(x)       ((x & 3UL) << 2*9)
#define MODER8(x)       ((x & 3UL) << 2*8)
#define MODER7(x)       ((x & 3UL) << 2*7)
#define MODER6(x)       ((x & 3UL) << 2*6)
#define MODER5(x)       ((x & 3UL) << 2*5)
#define MODER4(x)       ((x & 3UL) << 2*4)
#define MODER3(x)       ((x & 3UL) << 2*3)
#define MODER2(x)       ((x & 3UL) << 2*2)
#define MODER1(x)       ((x & 3UL) << 2*1)
#define MODER0(x)       ((x & 3UL) << 0)

#define AFRx7(x)        ((x & 0xfUL) << 4*7)
#define AFRx6(x)        ((x & 0xfUL) << 4*6)
#define AFRx5(x)        ((x & 0xfUL) << 4*5)
#define AFRx4(x)        ((x & 0xfUL) << 4*4)
#define AFRx3(x)        ((x & 0xfUL) << 4*3)
#define AFRx2(x)        ((x & 0xfUL) << 4*2)
#define AFRx1(x)        ((x & 0xfUL) << 4*1)
#define AFRx0(x)        ((x & 0xfUL) << 4*0)

#define AF15            15
#define AF14            14
#define AF13            13
#define AF12            12
#define AF11            11
#define AF10            10
#define AF9             9
#define AF8             8
#define AF7             7
#define AF6             6
#define AF5             5
#define AF4             4
#define AF3             3
#define AF2             2
#define AF1             1
#define AF0             0

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

#define SYSTICK_ID 10
#define SYSCALL_ID 1

#define FALSE 0
#define TRUE 1

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _SO_ */