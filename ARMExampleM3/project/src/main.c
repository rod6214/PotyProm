#include "so.h"

int main() { 
    reset_list();
    CLOCK_start_default();  
    int last = CLOCK_GetTick();

    while(1) 
    {
        int now = CLOCK_GetTick();
        if ((now - last) >= 10)
        {
            last = CLOCK_GetTick();
        }
    }
    return 0;
}

