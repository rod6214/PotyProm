#include "so.h"
#include "gpio.h"

SO_Input_t input;

int main() {    
    // CLOCK_start_default();
    // FMC_SDRAM_prepare_ports();
    // FMC_SDRAM_start_default();

    // volatile uint32_t *space = (uint32_t*)SDRAM_BANK_2;
    // *space = 78;

    // // Change memory map to sdram
    // // SYSCFG->SYSCFG_MEMRM = MEM_MODE(4);
    // RCC->APB2ENR |= SELECT_BIT(14);

    // volatile SYSCFG_t * test = SYSCFG;
    // test->SYSCFG_MEMRM = MEM_MODE(4);

    // // entry_point();
    // CALL_OPERATING_SYSTEM();
    
    while(1) {}
    return 0;
}

