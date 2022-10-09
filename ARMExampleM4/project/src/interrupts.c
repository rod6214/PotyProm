#include "so.h"
#include "gpio.h"

#define MAX_SYSCALL 32
Subs_t __mem[MAX_SYSCALL];
int idx = 0;

static void reorder();
static void invoke(int code);
extern int main();

void HardFault_Handler() 
{}

void Reset_Handler() 
{
    main();
}

void SysTick_Handler() 
{
    invoke(SYSTICK_ID);
}

void SVC_Handler(int code) 
{
    invoke(code);
}

// void BOOT_OperatingSystem(uint32_t address) 
// {
//     asm volatile ("b %0"::"m"(address));
// }

static void invoke(int code) 
{
    if (idx > MAX_SYSCALL)
        return;
    for (int i = 0; i < MAX_SYSCALL; i++) 
    {
        if (__mem[i].code == code
            && __mem[i].callback != NULL) 
            {
                __mem[i].callback();
                break;
            }
    }
}

void reset_list() 
{
    idx = 0;
}

void add_subscriber(Subs_t subscriber)
{
    if (subscriber.code == 0 ||
        subscriber.callback == NULL)
        return;
    reorder();
    __mem[idx].code = subscriber.code;
    __mem[idx].callback = subscriber.callback;
    idx++;
}

void remove_subscriber(Subs_t subscriber)
{
    if (subscriber.callback == NULL)
        return;
    for (int i = 0; i < MAX_SYSCALL && idx > 0; i++)
    {
        if (__mem[i].callback != NULL)
        {
            if (__mem[i].callback == subscriber.callback)
            {
                __mem[i].callback = NULL;
                break;
            }
        }
    }

    idx--;
}

static void reorder() 
{
    for (int i = 0; i < MAX_SYSCALL && idx > 0; i++)
    {
        if (__mem[i].callback == NULL)
        {
            for (int j = i + 1; j < MAX_SYSCALL; j++)
            {
                if (__mem[j].callback != 0)
                {
                    Subs_t head = __mem[i];
                    Subs_t tail = __mem[j];
                    __mem[i] = tail;
                    __mem[j] = head;
                    break;
                }
            }
        }
    }
}
