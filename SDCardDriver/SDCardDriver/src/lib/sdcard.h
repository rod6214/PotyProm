#ifndef _sd_card_h
#define _sd_card_h

#define SD_IN_IDLE_STATE    0x01
#define SD_READY            0x00
#define SD_R1_NO_ERROR(X)   X < 0x02

#define R3_BYTES            4
#define R7_BYTES            4

#define CMD0_MAX_ATTEMPTS       255
#define CMD55_MAX_ATTEMPTS      255
#define SD_ERROR                1
#define SD_SUCCESS              0
#define SD_MAX_READ_ATTEMPTS    1563
#define SD_READ_START_TOKEN     0xFE
#define SD_INIT_CYCLES          80

#define SD_START_TOKEN          0xFE
#define SD_ERROR_TOKEN          0x00

#define SD_DATA_ACCEPTED        0x05
#define SD_DATA_REJECTED_CRC    0x0B
#define SD_DATA_REJECTED_WRITE  0x0D

#define SD_BLOCK_LEN            512
#define SD_CARD_ERROR_ACMD41    0x08
#define SD_CARD_TYPE_SD1        1
#define SD_CARD_TYPE_SD2        2
#define SD_CARD_ERROR_CMD8      2
#define SD_CARD_ERROR_CMD0      1
#define SD_CARD_ERROR_CMD58     6
#define SD_CARD_TYPE_SDHC       3
#define SD_INIT_TIMEOUT         2000
#define SD_CARD_ERROR_SCK_RATE  22

/** Set SCK to max rate of F_CPU/2. See Sd2Card::setSckRate(). */
#define SPI_FULL_SPEED 0
/** Set SCK rate to F_CPU/4. See Sd2Card::setSckRate(). */
#define SPI_HALF_SPEED 1
/** Set SCK rate to F_CPU/8. Sd2Card::setSckRate(). */
#define SPI_QUARTER_SPEED 2

#define SD_CARD_ERROR_ERASE_SINGLE_BLOCK 11
// #define CMD32 32
// #define CMD33 33
// #define CMD38 38
#define SD_CARD_ERROR_ERASE 10
#define SD_ERASE_TIMEOUT 10000
#define SD_CARD_ERROR_ERASE_TIMEOUT 12
#define SD_CARD_ERROR_READ_REG 14
#define SD_READ_TIMEOUT 13
#define SD_CARD_ERROR_READ_TIMEOUT 15
#define SD_CARD_ERROR_READ 13
#define SD_CARD_ERROR_CMD17 3
#define SD_CARD_ERROR_CMD24 4
#define DATA_START_BLOCK 254
#define SD_WRITE_TIMEOUT 600
#define SD_CARD_ERROR_WRITE_TIMEOUT 21
#define SD_CARD_ERROR_WRITE_PROGRAMMING 20
#define SD_CARD_ERROR_WRITE 17
#define SD_CARD_ERROR_WRITE_MULTIPLE 19
#define SD_CARD_ERROR_ACMD23 7
#define SD_CARD_ERROR_CMD25 5
#define SD_CARD_ERROR_STOP_TRAN 16


#ifdef __cplusplus
extern "C" {
#endif
// SD functions
uint8_t SDCARD_init(uint8_t sckRateID, uint8_t chipSelectPin);
uint8_t SDCARD_CardCommand(uint8_t cmd, uint32_t arg);
uint8_t SDCARD_CardCommand(uint8_t cmd, uint32_t arg);
uint8_t SDCARD_readData(uint32_t block,
                          uint16_t offset, uint16_t count, uint8_t* dst);
uint8_t SDCARD_writeData2(uint8_t token, const uint8_t* src);
uint8_t SDCARD_writeData(const uint8_t* src);
uint8_t SDCARD_writeBlock(uint32_t blockNumber, const uint8_t* src, uint8_t blocking);
uint8_t SDCARD_readBlock(uint32_t block, uint8_t* dst);
void SDCARD_partialBlockRead(uint8_t value);
uint8_t SDCARD_eraseSingleBlockEnable(void);
uint8_t SDCARD_readRegister(uint8_t cmd, void* buf);
uint8_t SDCARD_setSckRate(uint8_t sckRateID);
uint8_t SDCARD_SetSpiClock(uint32_t clock);
uint8_t SDCARD_waitNotBusy(unsigned int timeoutMillis);
uint8_t SDCARD_waitStartBlock(void);
uint8_t SDCARD_writeStart(uint32_t blockNumber, uint32_t eraseCount);
uint8_t SDCARD_writeStop(void);
uint8_t SDCARD_isBusy(void);
void SDCARD_readEnd(void);
void chipSelectLow(void);
void chipSelectHigh(void);
// void SD_powerUpSeq(void);
// void SD_command(uint8_t cmd, uint32_t arg, uint8_t crc);
// uint8_t SD_readRes1(void);
// void SD_readRes2(uint8_t *res);
// void SD_readRes3(uint8_t *res);
// void SD_readRes7(uint8_t *res);
// void SD_readBytes(uint8_t *res, uint8_t n);
// uint8_t SD_goIdleState(void);
// void SD_sendIfCond(uint8_t *res);
// void SD_sendStatus(uint8_t *res);
// void SD_readOCR(uint8_t *res);
// uint8_t SD_sendApp(void);
// uint8_t SD_sendOpCond(void);
// uint8_t SD_readSingleBlock(uint32_t addr, uint8_t *buf, uint8_t *error);
// uint8_t SD_writeSingleBlock(uint32_t addr, uint8_t *buf, uint8_t *res);
#ifdef __cplusplus
}
#endif
#endif