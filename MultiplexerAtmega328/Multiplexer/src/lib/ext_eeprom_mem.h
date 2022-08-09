/*
 * ext_eeprom_mem.h
 *
 * Created: 5/7/2022 7:38:37 PM
 *  Author: Nelson
 */ 


#ifndef EXT_EEPROM_MEM_H_
#define EXT_EEPROM_MEM_H_

typedef struct 
{
	union 
	{
		struct
		{
			char bytesl;
			char bytesh;
		};
		int bytes;	
	};
	union 
	{
		struct
		{
			char offsetl;
			char offseth;
		};	
		int offset;	
	};
	
	char* data;
	
} EEPROM_t;


extern void write_mem(int address, char data);
extern char read_mem(int address);
extern void prepare_for_write();
extern void prepare_for_read();
extern EEPROM_t* get_eeprom(char* buffer);

#endif /* EXT_EEPROM_MEM_H_ */