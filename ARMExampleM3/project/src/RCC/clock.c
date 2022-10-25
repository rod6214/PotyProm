#include "so.h"

extern void incrementTick();
int RTC_config();

uint32_t _tick;

Subs_t rtc_sub = { 
    .code = RTC_ID, 
    .callback = incrementTick 
};

#define RTC_Has_terminated() (RTC->CRL&RTC_CRL_RTOFF)

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

    RTC_config();
}

int RTC_config() 
{
    RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    // Note: If the HSE divided by 128 is used as the RTC clock, this bit must remain set to 1.
    SET_BIT(PWR->CR, PWR_CR_DBP);
    
    SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
    RCC->BDCR |= RCC_BDCR_RTCSEL_HSE;

    int attempts = 0;
    RTC->CRL |= RTC_CRL_CNF;
    // RTC->CRH |= RTC_CRH_SECIE | RTC_CRH_OWIE;
    RTC->CNTH = 0;
    RTC->CNTL = 0;
    RTC->PRLH = 0;
    RTC->PRLL = 65;
    RTC->CRL &= ~RTC_CRL_CNF;
    while(!RTC_Has_terminated() && attempts <= 10) 
        attempts++;
    
    if (attempts == 10)
        return ERROR;
    #if defined(_TICK_WITH_IRQn)
    add_subscriber(rtc_sub);
    enable_IRQn(RTC_IRQn);
    #endif

    return SUCCESS;
}

uint32_t CLOCK_GetTick() 
{
    #if !defined(_TICK_WITH_IRQn)
    _tick = (RTC->CNTH << 16UL) | RTC->CNTL;
    #endif
    return _tick;
}

void CLOCK_Delay(uint32_t value) 
{
    int exit = FALSE;
    uint32_t last = CLOCK_GetTick();
    while(!exit) 
    {
        uint32_t now = CLOCK_GetTick();
        if ((now - last) >= value) 
        {
            last = CLOCK_GetTick();
            exit = TRUE;
        }
    }
}

#if defined(_TICK_WITH_IRQn)
void incrementTick() 
{
    int attempts = 0;
    RTC->CRL |= RTC_CRL_CNF;
    RTC->CRL &= ~RTC_CRL_SECF;
    _tick++;
    RTC->CRL &= ~RTC_CRL_CNF;
    while(!RTC_Has_terminated() && attempts <= 10) 
        attempts++;
}
#endif

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
