#include "so.h"
#include "gpio.h"

#define MAX_SYSCALL 20
Subs_t __mem[MAX_SYSCALL];
int idx = 0;

static void reorder_syscalls();

void Reset_Handler() 
{}

void SysTick_Handler() 
{}

void SVC_Handler(int code) 
{
    if (idx > 20)
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

void reset_syscall_list() 
{
    idx = 0;
}

void add_syscall_subscriber(Subs_t subscriber)
{
    if (subscriber.code == 0 ||
        subscriber.callback == NULL)
        return;
    reorder_syscalls();
    __mem[idx].code = subscriber.code;
    __mem[idx].callback = subscriber.callback;
    idx++;
}

void remove_syscall_subscriber(Subs_t subscriber)
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

static void reorder_syscalls() 
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
