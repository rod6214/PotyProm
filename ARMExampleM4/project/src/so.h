
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
#define SDRAM_BASE 0x60000000
#define GPIOC_BASE 0x40020800

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
          uint32_t RESERVED0[1];
    __IOM uint32_t APB1RSTR;
    __IOM uint32_t APB2RSTR;
          uint32_t RESERVED1[2];
    __IOM uint32_t AHB1ENR;
    __IOM uint32_t AHB2ENR;
    __IOM uint32_t AHB3ENR;
          uint32_t RESERVED2[1];
    __IOM uint32_t APB1ENR;
    __IOM uint32_t APB2ENR;
          uint32_t RESERVED3[2];
    __IOM uint32_t AHB1LPENR;
    __IOM uint32_t AHB2LPENR;
    __IOM uint32_t AHB3LPENR;
          uint32_t RESERVED4[1];
    __IOM uint32_t APB1LPENR;
    __IOM uint32_t APB2LPENR;
          uint32_t RESERVED5[2];
    __IOM uint32_t BDCR;
    __IOM uint32_t CSR;
          uint32_t RESERVED6[2];
    __IOM uint32_t SSCGR;
    __IOM uint32_t PLLI2SCFGR;
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

#define SCB ((SCB_Type*)0xE000ED00UL)   /*!< SCB configuration struct */
#define SYSTICK ((SysTick_t*)0xE000E010UL)   /*!< SYSTICK configuration struct */
#define RCC ((RCC_t*)0x40023800UL)   /*!< SYSTICK configuration struct */
#define SDRAMC (SDRAM_C_t*)SDRAM_CONTROLLER
#define GPIOC ((GPIO_t*)GPIOC_BASE);

#define SELECT_BIT(x) (1 << x)

#define GPIOCEN        SELECT_BIT(2)

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
#define MEMHIZ(x)       ((x & 0xff) << 24)
#define MEMHOLD(x)      ((x & 0xff) << 16)
#define MEMWAIT(x)      ((x & 0xff) << 8)
#define MEMSET(x)       ((x & 0xff) << 0)
//
#define ATTHIZ(x)       ((x & 0xff) << 24)
#define ATTHOLD(x)      ((x & 0xff) << 16)
#define ATTWAIT(x)      ((x & 0xff) << 8)
#define ATTSET(x)       ((x & 0xff) << 0)
//
#define IOHIZ(x)        ((x & 0xff) << 24)
#define IOHOLD(x)       ((x & 0xff) << 16)
#define IOWAIT(x)       ((x & 0xff) << 8)
#define IOSET(x)        ((x & 0xff) << 0)
//
#define RPIPE(x)        ((x & 3) << 13)
#define RBURST          SELECT_BIT(12)
#define CLK(x)          ((x & 3) << 10)
#define WP              SELECT_BIT(9)
#define CAS(x)          ((x & 3) << 7) 
#define NB              SELECT_BIT(6)
#define NR(x)           ((x & 3) << 2)
#define NC(x)           ((x & 3) << 0)
//
#define TRCD(x)         ((x & 0xf) << 24)
#define TRP(x)          ((x & 0xf) << 20)
#define TWR(x)          ((x & 0xf) << 16)
#define TRC(x)          ((x & 0xf) << 12)
#define TRAS(x)         ((x & 0xf) << 8)
#define TXSR(x)         ((x & 0xf) << 4)
#define TMRD(x)         ((x & 0xf) << 0)
//
#define MRD(x)          ((x & 0x1fff) << 9)
#define NRFS(x)         ((x & 0xf) << 8)
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

#define MODER15(x)      ((x & 3) << 2*15)
#define MODER14(x)      ((x & 3) << 2*14)
#define MODER13(x)      ((x & 3) << 2*13)
#define MODER12(x)      ((x & 3) << 2*12)
#define MODER11(x)      ((x & 3) << 2*11)
#define MODER10(x)      ((x & 3) << 2*10)
#define MODER9(x)       ((x & 3) << 2*9)
#define MODER8(x)       ((x & 3) << 2*8)
#define MODER7(x)       ((x & 3) << 2*7)
#define MODER6(x)       ((x & 3) << 2*6)
#define MODER5(x)       ((x & 3) << 2*5)
#define MODER4(x)       ((x & 3) << 2*4)
#define MODER3(x)       ((x & 3) << 2*3)
#define MODER2(x)       ((x & 3) << 2*2)
#define MODER1(x)       ((x & 3) << 2*1)
#define MODER0(x)       ((x & 3) << 0)

extern void ___syscall(int code);
extern void add_subscriber(Subs_t subscriber);
extern void remove_subscriber(Subs_t subscriber);
extern void Reset_Handler(void);
extern void SVC_Handler(int code);
extern void SysTick_Handler();
extern void reset_list();
extern void HardFault_Handler();
extern void CLOCK_start_default(RCC_t* pclock);
extern void FMC_SDRAM_start_default(SDRAM_C_t* psdram);
extern void CLOCK_enable_FMC(RCC_t* pclock);
extern void CLOCK_reset_FMC(RCC_t* pclock);
extern void CLOCK_enable_GPIOC(RCC_t* pclock);

#define SYSTICK_ID 10
#define SYSCALL_ID 1

#define FALSE 0
#define TRUE 1

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _SO_ */