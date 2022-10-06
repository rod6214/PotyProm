#include "so.h"

void FMC_SDRAM_start_default(SDRAM_C_t* psdram) 
{
    CLOCK_enable_FMC(RCC);
    // psdram->SDCR_1 = CLK(2);
    psdram->SDCR_1 |= RPIPE(2) | RBURST | CLK(2) | CAS(2);
    psdram->SDCR_2 |= RPIPE(2) | RBURST | CLK(2) | CAS(2);
    // psdram->SDCR_1 = 0x4954;
    // psdram->SDTR1 = 0x1111311;
    // psdram->SDTR1 |= TRP(1) | TRC(3);
    // psdram->SDTR2 |= TRP(1) | TRC(3);
    psdram->SDTR1 = TRCD(1) | TRP(1) | TRAS(3) | TWR(1) | TMRD(2) | TRC(4) | TXSR(7);
    psdram->SDCMR = CTB1 | CTB2 | MODE(1);
    int i = 0;
    while(i < 100000) i++;
    psdram->SDCMR = CTB1 | CTB2 | MODE(2);
    psdram->SDCMR = CTB1 | CTB2 | MODE(3) | NRFS(4);
    psdram->SDCMR = CTB1 | CTB2 | MODE(4) | MRD(0x31) | NRFS(4);
    psdram->SDRTR = COUNT(636);
}

void FMC_SDRAM_prepare_ports() 
{
    GPIO_t *gpioB, *gpioC, *gpioD, *gpioE,
    *gpioF, *gpioG, *gpioH, *gpioI;

    gpioB = GPIOB;
    gpioC = GPIOC;
    gpioD = GPIOD;
    gpioE = GPIOE;
    gpioF = GPIOF;
    gpioG = GPIOG;
    gpioH = GPIOH;
    gpioI = GPIOI;

    gpioB->GPIOx_MODER = MODER5(2) | MODER6(2) | MODER7(2);
    gpioC->GPIOx_MODER = MODER3(2) | MODER2(2) | MODER0(2);
    gpioD->GPIOx_MODER = MODER0(2) | MODER1(2) | MODER2(2)|
                        MODER3(2) | MODER4(2) | MODER5(2) |
                        MODER6(2) | MODER7(2) | MODER8(2) |
                        MODER9(2) | MODER10(2) | MODER11(2) |
                        MODER12(2) | MODER13(2) | MODER14(2) | MODER15(2);
    gpioE->GPIOx_MODER = MODER0(2) | MODER1(2) | MODER2(2)|
                        MODER3(2) | MODER4(2) | MODER5(2) |
                        MODER6(2) | MODER7(2) | MODER8(2) |
                        MODER9(2) | MODER10(2) | MODER11(2) |
                        MODER12(2) | MODER13(2) | MODER14(2) | MODER15(2);
    gpioF->GPIOx_MODER = MODER0(2) | MODER1(2) | MODER2(2)|
                        MODER3(2) | MODER4(2) | MODER5(2) |
                        MODER6(2) | MODER7(2) | MODER8(2) |
                        MODER9(2) | MODER10(2) | MODER11(2) |
                        MODER12(2) | MODER13(2) | MODER14(2) | MODER15(2);
    gpioG->GPIOx_MODER = MODER0(2) | MODER1(2) | MODER2(2)|
                        MODER3(2) | MODER4(2) | MODER5(2) |
                        MODER6(2) | MODER7(2) | MODER8(2) |
                        MODER9(2) | MODER10(2) | MODER11(2) |
                        MODER12(2) | MODER13(2) | MODER14(2) | MODER15(2);
    gpioH->GPIOx_MODER = MODER0(2) | MODER1(2) | MODER2(2)|
                        MODER3(2) | MODER4(2) | MODER5(2) |
                        MODER6(2) | MODER7(2) | MODER8(2) |
                        MODER9(2) | MODER10(2) | MODER11(2) |
                        MODER12(2) | MODER13(2) | MODER14(2) | MODER15(2);
    gpioI->GPIOx_MODER = MODER0(2) | MODER1(2) | MODER2(2)|
                        MODER3(2) | MODER4(2) | MODER5(2) |
                        MODER6(2) | MODER7(2) | MODER8(2) |
                        MODER9(2) | MODER10(2) | MODER11(2) |
                        MODER12(2) | MODER13(2) | MODER14(2) | MODER15(2);
    //////////////////////////////////////////////////////////////////////
    gpioB->GPIOx_AFRL = AFRx7(AF12) | AFRx6(AF12) | AFRx5(AF12);
    gpioC->GPIOx_AFRL = AFRx3(AF12) | AFRx2(AF12) | AFRx0(AF12);
    gpioD->GPIOx_MODER = AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12)|
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12);
    gpioE->GPIOx_MODER = AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12)|
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12);
    gpioF->GPIOx_MODER = AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12)|
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12);
    gpioG->GPIOx_MODER = AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12)|
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12);
    gpioH->GPIOx_MODER = AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12)|
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12);
    gpioI->GPIOx_MODER = AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12)|
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) |
                        AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12) | AFRx7(AF12);
 
    CLOCK_enable_AHB1(GPIOB_EN | GPIOC_EN | GPIOD_EN | GPIOE_EN | 
                        GPIOF_EN | GPIOG_EN | GPIOH_EN | GPIOI_EN);
}
