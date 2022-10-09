#include "so.h"

#define MODE_INPUT 	0
#define MODE_GPIO		1
#define MODE_AF			2
#define MODE_ANALOG	3

#define TYPE_PUSHPULL 	0
#define TYPE_OPENDRAIN 	1

#define SPEED_2MHz		0
#define SPEED_25MHz		1
#define SPEED_50MHz		2
#define SPEED_100MHz	3

#define PULLUP_NONE		0
#define PULLUP_UP			1
#define PULLUP_DOWN		2

#define MASK1BIT(pin) ((uint32_t)~(1 << (pin * 1)))
#define MASK2BIT(pin) ((uint32_t)~(3 << (pin * 2)))
#define MASK4BIT(pin) ((uint32_t)~(15 << (pin * 4)))
#define AFMASKL(pin)	((uint32_t)~(15 << (pin * 4)))
#define AFMASKH(pin)	((uint32_t)~(15 << ((pin - 8) * 4)))

static  GPIO_t * const GPIOInitTable[] = {
		GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOF, GPIOG, GPIOG,
		GPIOD, GPIOD, GPIOD, GPIOD, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,
		GPIOD, GPIOD, GPIOD,
		GPIOB, GPIOB, GPIOC, GPIOE, GPIOE, GPIOF, GPIOG, GPIOG, GPIOG, GPIOG,
		GPIOH, GPIOH, GPIOH, GPIOH, GPIOH, GPIOH, GPIOH, GPIOH, GPIOH, GPIOH, GPIOH,
		0
};
static uint8_t const PINInitTable[] = {
		0, 1, 2, 3, 4, 5, 12, 13, 14, 15, 0, 1,
		14, 15, 0, 1, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		8, 9, 10,
		5, 6, 0, 0, 1, 11, 4, 5, 8, 15,
        5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		0
};

void gpio_conf(GPIO_t * GPIO, uint8_t pin, uint8_t mode, uint8_t type, uint8_t speed, uint8_t pullup, uint8_t af)
{
		GPIO->GPIOx_MODER 	= (GPIO->GPIOx_MODER   & MASK2BIT(pin))   | (mode << (pin * 2));
		GPIO->GPIOx_OTYPER 	= (GPIO->GPIOx_OTYPER  & MASK1BIT(pin))   | (type << pin);
		GPIO->GPIOx_OSPEEDR = (GPIO->GPIOx_OSPEEDR & MASK2BIT(pin))   | (speed << (pin * 2));
		GPIO->GPIOx_PUPDR		= (GPIO->GPIOx_PUPDR   & MASK2BIT(pin))		| (pullup << (pin * 2));
		if(pin > 7)
			{
				GPIO->GPIOx_AFRH = (GPIO->GPIOx_AFRH & AFMASKH(pin)) | (af << ((pin - 8) * 4));
			}
		else
			{
				GPIO->GPIOx_AFRL = (GPIO->GPIOx_AFRL & AFMASKL(pin)) | (af << ((pin) * 4));
			}
}

void FMC_SDRAM_start_default() 
{
    volatile uint32_t ptr = 0;
	volatile uint32_t i = 0;
    SDRAM_C_t* psdram = (SDRAM_C_t*)SDRAM_CONTROLLER;
    CLOCK_enable_FMC();
    // Initialization step 1
    psdram->SDCR_1 = FMC_SDCR1_SDCLK_1  | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE_1;
    psdram->SDCR_2 = FMC_SDCR1_NR_0	  | FMC_SDCR1_MWID_0 | FMC_SDCR1_NB | FMC_SDCR1_CAS;
    // Initialization step 2
    psdram->SDTR1 = TRC(7)  | TRP(2);
    psdram->SDTR2 = TMRD(2) | TXSR(7) | TRAS(4) | TWR(2) | TRCD(2);
    // Initialization step 3
    while(psdram->SDSR & FMC_SDSR_BUSY);
    psdram->SDCMR = CTB2 | MODE(1) | NRFS(1);
    // Initialization step 4
    for(i = 0; i  < 1000000; i++);
    // Initialization step 5
    while(psdram->SDSR & FMC_SDSR_BUSY);
    psdram->SDCMR = CTB2 | MODE(2) | NRFS(2);
    // Initialization step 6
    while(psdram->SDSR & FMC_SDSR_BUSY);
    psdram->SDCMR = CTB2 | MODE(3) | NRFS(4);
    // Initialization step 7
    while(psdram->SDSR & FMC_SDSR_BUSY);
    psdram->SDCMR = CTB2 | MODE(4) | MRD(0x231) | NRFS(1);
    // Initialization step 8
    while(psdram->SDSR & FMC_SDSR_BUSY);
    psdram->SDRTR = COUNT(683);
    while(psdram->SDSR & FMC_SDSR_BUSY){}
    // Clear SDRAM
	for(ptr = SDRAM_BASE; ptr < (SDRAM_BASE + SDRAM_SIZE); ptr += 4)
    {
        *((uint32_t *)ptr) = 0xFFFFFFFF;
        while(psdram->SDSR & FMC_SDSR_BUSY);
    }
}

void FMC_SDRAM_prepare_ports() 
{
    volatile uint32_t i = 0;

    CLOCK_enable_AHB1(RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOHEN);

    while(GPIOInitTable[i] != 0){
        if (i >= 38) 
        {
            int* pepe = (int*)0x20001000;
            *pepe = 45;
        }
		gpio_conf(GPIOInitTable[i], PINInitTable[i],  MODE_AF, TYPE_PUSHPULL, SPEED_100MHz, PULLUP_NONE, 12);
		i++;
	}
}
