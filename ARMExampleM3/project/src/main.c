#include "so.h"

int main() { 
    asm("svc 0");   
    while(1) {}
    return 0;
}

