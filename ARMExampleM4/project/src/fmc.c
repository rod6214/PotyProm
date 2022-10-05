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
