#include "so.h"

int main() { 
    reset_list();
    CLOCK_start_default();  
    uint32_t last = CLOCK_GetTick();

    while(1) 
    {
        uint32_t now = CLOCK_GetTick();
        if ((now - last) >= 10)
        {
            last = CLOCK_GetTick();
        }
    }
    return 0;
}

