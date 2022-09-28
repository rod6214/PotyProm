#include "so.h"
#include "gpio.h"

void test_callback() 
{
    asm("nop");
}

void test_callback2() 
{
    asm("nop");
}

void test_callback3() 
{
    asm("nop");
}

int main() {
    Subs_t subs = {1, test_callback};
    Subs_t subs2 = {2, test_callback2};
    Subs_t subs3 = {3, test_callback3};
    Subs_t subs4 = {4, test_callback3};
    reset_syscall_list();
    add_syscall_subscriber(subs);
    add_syscall_subscriber(subs2);
    add_syscall_subscriber(subs3);
    ___syscall(2);
    ___syscall(3);
    ___syscall(1);
    remove_syscall_subscriber(subs2);
    add_syscall_subscriber(subs4);
    ___syscall(2);
    ___syscall(4);
    while(1) {}
    return 0;
}

