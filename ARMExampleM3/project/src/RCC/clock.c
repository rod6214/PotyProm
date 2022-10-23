#include "so.h"

void CLOCK_start_default() 
{
    RCC->CIR &= ~RCC_CIR_PLLRDYIE;
    RCC->CFGR |= RCC_CFGR_PLLSRC;

    if (!(RCC->CR & RCC_CR_HSERDY)) 
    {
        // Activate HSE oscillator
        RCC->CR |= RCC_CR_HSEON;
        // Wait until HSE oscillator is ready
        while(!(RCC->CR & RCC_CR_HSERDY));
    }

    if (!(RCC->CR & RCC_CR_HSIRDY)) 
    {
        // Activate HSE oscillator
        RCC->CR |= RCC_CR_HSION;
        // Wait until HSE oscillator is ready
        while(!(RCC->CR & RCC_CR_HSIRDY));
    }

    // Setup system PLL clock at 72Mhz
    RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9;
    // Setup APB2 and APB1 clocks at 36Mhz
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
    RCC->CFGR &= ~RCC_CFGR_USBPRE;
    
    // Activate main PLL
    RCC->CR |= RCC_CR_PLLON;

    // Wait until main PLL is ready
    while(!(RCC->CR & RCC_CR_PLLRDY));
    
    if (!((RCC->CFGR) & RCC_CFGR_SW_PLL)) 
    {
        FLASH->ACR = (FLASH->ACR&(~FLASH_ACR_LATENCY)) | (FLASH_ACR_LATENCY_2);
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        while(!((RCC->CFGR) & RCC_CFGR_SWS_PLL));
    }

    RCC->CR |= RCC_CR_CSSON;
}

void CLOCK_enable_FMC() 
{
    // RCC->AHB3ENR |= FMCEN;
}

void CLOCK_reset_FMC() 
{
    // RCC->AHB3RSTR |= FMCRST;
}

void CLOCK_enable_AHB1(uint32_t values) 
{
    // RCC->AHB1ENR |= values;
}
