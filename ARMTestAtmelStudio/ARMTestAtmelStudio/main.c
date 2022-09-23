/*
 * ARMTestAtmelStudio.c
 *
 * Created: 8/25/2022 1:50:14 PM
 * Author : Nelson
 */ 


#include "sam.h"
//#include <sys/signal.h>

extern void system_call();

int main(void)
{
    /* Initialize the SAM system */
    //SystemInit();
	
	system_call();
    /* Replace with your application code */
    while (1) 
    {
    }
}
