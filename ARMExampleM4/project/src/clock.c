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
    pclock->PLLCFGR |= PLLQ2 | PLLSRC | PLLP0 | PLLN8 | PLLN5 | PLLN3 | PLLN2 | PLLM2;
    // pclock->CFGR = PPRE22 | PPRE12 | PPRE10;

    // Activate main PLL
    pclock->CR |= PLLON;
    // Wait until main PLL is ready
    while(!(pclock->CR & PLLRDY));

    if (!((pclock->CFGR) & SWS1)) 
    {
        pclock->CFGR |= SW1;
        while(!((pclock->CFGR) & SWS1));
    }

    pclock->CR |= CSSON;
}