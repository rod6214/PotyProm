#define I2C_READ 1
#define I2C_WRITE 0
#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0
void EEPROM_init(uint8_t clock);
void EEPROM_Write(unsigned int addr, unsigned char ldata, unsigned char device);
unsigned char EEPROM_Read(unsigned int addr, unsigned char device);
void EEPROM_Write_Page(unsigned int add, unsigned char *ldata, unsigned char len, unsigned char device);
void EEPROM_Read_Page(unsigned int add, unsigned char *ldata, unsigned int len, unsigned char device);