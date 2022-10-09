#include "../so.h"

void syscall_handler(int code) 
{
    asm("nop");
}

SO_ENTRY int Tmain(void *obj) {
    SO_Input_t* handlers = (SO_Input_t*)obj;
    Subs_t subs = {1, syscall_handler};

    handlers->add_subscriber(subs);
    handlers->syscall(1);
    
    while(1){}
    return 0;
}