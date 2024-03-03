#ifndef __SPI_H__
#define __SPI_H__

/*******************************************************************************
*   spi.h v1 - 11/02/2018
        Initial definitions
*   spi.h v2 - 11/07/2018
        Updated initialization function
*******************************************************************************/

// pin definitions
#define DDR_SPI             DDRB
#define PORT_SPI            PORTB
#define CS                  PINB2
#define SS                  CS
#define MOSI                PINB3
#define MISO                PINB4
#define SCK                 PINB5

#ifndef __cplusplus
#define SD_CHIP_SELECT_PIN  SS
/** SPI Master Out Slave In pin */
#define SPI_MOSI_PIN  MOSI
/** SPI Master In Slave Out pin */
#define SPI_MISO_PIN  MISO
/** SPI Clock pin */
#define SPI_SCK_PIN  SCK
#define SS_PIN SD_CHIP_SELECT_PIN
#endif

// macros
#define CS_ENABLE()         PORT_SPI &= ~(1 << CS)
#define CS_DISABLE()        PORT_SPI |= (1 << CS)

// initialization definitions
#define SPI_MASTER          0b0001000000000000
#define SPI_SLAVE           0b0000000000000000
#define SPI_FOSC_4          0b0000000000000000
#define SPI_FOSC_16         0b0000000100000000
#define SPI_FOSC_64         0b0000001000000000
#define SPI_FOSC_128        0b0000001100000000
#define SPI_2X_FOSC_2       0b0000000000000001
#define SPI_2X_FOSC_8       0b0000000100000001
#define SPI_2X_FOSC_32      0b0000001000000001
#define SPI_2X_FOSC_64      0b0000001100000001
#define SPI_INTERRUPTS      0b1000000000000000
#define SPI_MODE_0          0b0000000000000000
#define SPI_MODE_1          0b0000010000000000
#define SPI_MODE_2          0b0000100000000000
#define SPI_MODE_3          0b0000110000000000
#define SPI_DEFAULT         SPI_MASTER | SPI_FOSC_128 | SPI_MODE_0


#define SPI_MODE_MASK 0x0c
#define SPI_2XCLOCK_MASK 0x01
#define SPI_CLOCK_MASK 0x03
#define LSBFIRST 0
#define _BV(bit) (1 << (bit))





typedef struct  _SETTINGS__SPI
{
    uint8_t spcr;
    uint8_t spsr;
} SPISettings_t;

// SPI functions
// void SPI_init(uint16_t initParams);
uint8_t SPI_transfer(uint8_t data);
SPISettings_t SPI_settings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode);
void SPI_BeginTransaction(SPISettings_t settings);
void SPI_begin();
#endif