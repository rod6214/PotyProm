#include "so.h"
#include "gpio.h"

#define MAX_SYSCALL 20
Subs_t __mem[MAX_SYSCALL];
int idx = 0;

static void reorder_syscalls();

// extern void __EXTERNAL__ __syscall_handler(int code) 
// {
//     for (int i = 0; i < MAX_SYSCALL && idx > 0; i++) 
//     {
//         if (__mem[i].code == code) 
//         {
//             ((__mem[i].callback))();
//         }
//     }
// }

void add_syscall_subscriber(Subs_t subscriber)
{
    if (subscriber.code == 0)
        return;
    __mem[idx].code = subscriber.code;
    reorder_syscalls();
    idx++;
}

void remove_syscall_subscriber(Subs_t subscriber)
{
    if (subscriber.code == 0)
        return;
    for (int i = 0; i < MAX_SYSCALL && idx > 0; i++)
    {
        if (__mem[i].code != 0)
        {
            if (__mem[i].code == subscriber.code)
            {
                __mem[i].code = 0;
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
        if (__mem[i].code == 0)
        {
            for (int j = i + 1; j < MAX_SYSCALL; j++)
            {
                if (__mem[j].code != 0)
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
