#include "so.h"

void CLOCK_start_default(RCC_t* pclock) 
{
    if (!(pclock->CR & HSERDY)) 
    {
        // Activate HSE oscillator
        pclock->CR |= HSEON;
        // Wait until HSE oscillator is ready
        while(!(pclock->CR & HSERDY));
    }

    // Change system clock to PLL at 168Mhz
    pclock->PLLCFGR |= PLLQ2 | PLLSRC | PLLP(3) | PLLN(286) | PLLM(4);
    // pclock->CFGR = PPRE22 | PPRE12 | PPRE10;
    // HDCLK = SysClock / 2 at 84Mhz
    // pclock->CFGR |= HPRE3;
    pclock->CFGR |= MCO2PRE(6);
    pclock->CFGR &= ~HPRE(15);
    // Activate main PLL
    pclock->CR |= PLLON;

    // pclock->AHB3ENR |= FMCEN;
    // Wait until main PLL is ready
    while(!(pclock->CR & PLLRDY));

    if (!((pclock->CFGR) & SWS1)) 
    {
        pclock->CFGR |= SW1;
        while(!((pclock->CFGR) & SWS1));
    }

    pclock->CR |= CSSON;
}

void CLOCK_enable_FMC(RCC_t* pclock) 
{
    pclock->AHB3ENR |= FMCEN;
}

void CLOCK_reset_FMC(RCC_t* pclock) 
{
    pclock->AHB3RSTR |= FMCRST;
}

void CLOCK_enable_AHB1(uint32_t values) 
{
    RCC_t* pclock = RCC;
    pclock->AHB1ENR |= values;
}
