#include "so.h"
#include "USB/usbtypes.h"

int main() { 
    
    uint32_t last = CLOCK_GetTick();

    while(1) 
    {
        uint32_t now = CLOCK_GetTick();
        if ((now - last) >= 10)
        {
            last = (uint32_t)ep0_rx[0];
            last = (uint32_t)ep0_tx[0];
            last = CLOCK_GetTick();
        }
    }
    return 0;
}

