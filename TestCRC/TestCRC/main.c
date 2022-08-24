/*
 * TestCRC.c
 *
 * Created: 8/22/2022 11:09:32 PM
 * Author : Nelson
 */ 

#include <avr/io.h>

extern char CRCFn(char*);

char crtTable[8] = {0x51,0,0,0,0,0,0,0};

int main(void)
{
	char value = CRCFn(crtTable);
	//CRCFn(0);
    /* Replace with your application code */
    while (value != 0) 
    {
    }
}

