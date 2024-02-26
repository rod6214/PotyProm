#ifndef _sd_card_h
#define _sd_card_h

// command definitions
#define CMD0                0
#define CMD0_ARG            0x00000000
#define CMD0_CRC            0x94
// #define CMD0_CRC            0x4A
// #define CMD0_CRC            0x4A
#define CMD8                8
#define CMD8_ARG            0x0000001AA
#define CMD8_CRC            0x86
#define CMD9                9
#define CMD9_ARG            0x00000000
#define CMD9_CRC            0x00
#define CMD10               9
#define CMD10_ARG           0x00000000
#define CMD10_CRC           0x00
#define CMD13               13
#define CMD13_ARG           0x00000000
#define CMD13_CRC           0x00
#define CMD17               17
#define CMD17_CRC           0x00
#define CMD24               24
#define CMD24_CRC           0x00
#define CMD55               55
#define CMD55_ARG           0x00000000
#define CMD55_CRC           0x00
#define CMD58               58
#define CMD58_ARG           0x00000000
#define CMD58_CRC           0x00
#define ACMD41              41
#define ACMD41_ARG          0x40000000
#define ACMD41_CRC          0x00

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
#define R1_READY_STATE SD_READY
#define SD_CARD_ERROR_ACMD41    0x08
#define R1_IDLE_STATE           SD_IN_IDLE_STATE
#define R1_ILLEGAL_COMMAND      0x04
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


// SD functions
uint8_t SDCARD_init(uint8_t sckRateID, uint8_t chipSelectPin);
uint8_t SDCARD_CardCommand(uint8_t cmd, uint32_t arg);
uint8_t SDCARD_CardCommand(uint8_t cmd, uint32_t arg);
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

#endif