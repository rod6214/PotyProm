#include "so.h"
#include "gpio.h"

#define MAX_SYSCALL 32
Subs_t __mem[MAX_SYSCALL];
int idx;
extern unsigned int _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

static void reorder();
static void invoke(int code);
extern int main();
static void __initialize_data();

void HardFault_Handler() 
{}

void Reset_Handler() 
{
    reset_list();
    __initialize_data();
    CLOCK_start_default();  
    main();
}

void SysTick_Handler() 
{
    invoke(SYSTICK_ID);
}

void SVC_Handler() 
{
    invoke(SYSCALL_ID);
}

void RTC_Handler() 
{
    invoke(RTC_ID);
}

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

static void __initialize_data() 
{
    uint32_t *src_ptr = &_sidata;
    uint32_t *dest_ptr = &_sdata;
    uint32_t *last = &_edata;

    for (int i = 0; i < 2; i++) 
    {
        if (i > 0) 
        {
            dest_ptr = &_sbss;
            last = &_ebss;
        }

        while (dest_ptr != last) 
        {
            if (i > 0) 
            {
                *(dest_ptr++) = 0;
            }
            else
                *(dest_ptr++) = *(src_ptr++);
        }
    }
}
