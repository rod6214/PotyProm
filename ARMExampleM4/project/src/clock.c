#include "so.h"

void CLOCK_start_default() 
{
    if (!(RCC->CR & HSERDY)) 
    {
        // Activate HSE oscillator
        RCC->CR |= HSEON;
        // Wait until HSE oscillator is ready
        while(!(RCC->CR & HSERDY));
    }

    // Change system clock to PLL at 168Mhz
    // RCC->PLLCFGR |= PLLQ2 | PLLSRC | PLLP(3) | PLLN(286) | PLLM(4);
    RCC->PLLCFGR |= PLLQ2 | PLLSRC | PLLP(1) | PLLN(336) | PLLM(4);
    // pclock->CFGR = PPRE22 | PPRE12 | PPRE10;
    // HDCLK = SysClock / 2 at 84Mhz
    // pclock->CFGR |= HPRE3;
    RCC->CFGR |= MCO2PRE(6);
    RCC->CFGR &= ~HPRE(15);
    // Activate main PLL
    RCC->CR |= PLLON;

    // pclock->AHB3ENR |= FMCEN;
    // Wait until main PLL is ready
    while(!(RCC->CR & PLLRDY));

    if (!((RCC->CFGR) & SWS1)) 
    {
        RCC->CFGR |= SW1;
        while(!((RCC->CFGR) & SWS1));
    }

    RCC->CR |= CSSON;
}

void CLOCK_enable_FMC() 
{
    RCC->AHB3ENR |= FMCEN;
}

void CLOCK_reset_FMC() 
{
    RCC->AHB3RSTR |= FMCRST;
}

void CLOCK_enable_AHB1(uint32_t values) 
{
    RCC->AHB1ENR |= values;
}
