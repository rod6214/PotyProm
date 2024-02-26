#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "sdcard.h"
#include "arduino_generics.h"
#include "wiring.h"
#include "spi.h"

static uint32_t block_;
static uint8_t chipSelectPin_;
static uint8_t errorCode_;
static uint8_t inBlock_;
static uint16_t offset_;
static uint8_t partialBlockRead_;
static uint8_t status_;
static uint8_t type_;
static void spiSend(uint8_t b);
static uint8_t spiRec(void);
static void type(uint8_t value);
static uint8_t get_type(void);
static void error(uint8_t code);
static uint8_t setSckRate(uint8_t sckRateID);
static void readEnd(void);
static uint8_t waitNotBusy(unsigned int timeoutMillis);
static uint8_t cardAcmd(uint8_t cmd, uint32_t arg);
SPISettings_t settings;

/*******************************************************************************
 Initialize SD card
*******************************************************************************/
uint8_t SDCARD_init(uint8_t sckRateID, uint8_t chipSelectPin)
{
    errorCode_ = inBlock_ = partialBlockRead_ = type_ = 0;
  chipSelectPin_ = chipSelectPin;
  uint32_t arg;
  unsigned int t0 = millis();

    // set pin modes
  pinMode(chipSelectPin_, OUTPUT);
  digitalWrite(chipSelectPin_, HIGH);
  #ifndef USE_SPI_LIB
  pinMode(_BV(SPI_MISO_PIN), INPUT);
  pinMode(_BV(SPI_MOSI_PIN), OUTPUT);
  pinMode(_BV(SPI_SCK_PIN), OUTPUT);
  #endif

  #ifndef SOFTWARE_SPI
  #ifndef USE_SPI_LIB
  // SS must be in output mode even it is not chip select
  pinMode(_BV(SS_PIN), OUTPUT);
  digitalWrite(_BV(SS_PIN), HIGH); // disable any SPI device using hardware SS pin
  // Enable SPI, Master, clock rate f_osc/128
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
  // clear double speed
  SPSR &= ~(1 << SPI2X);
  #else // USE_SPI_LIB
  SPI_begin();
  settings = SPI_settings(250000, MSBFIRST, SPI_MODE0);
  #endif // USE_SPI_LIB
  #endif // SOFTWARE_SPI

  // must supply min of 74 clock cycles with CS high.
  #ifdef USE_SPI_LIB
  SPI_BeginTransaction(settings);
  #endif

  for (uint8_t i = 0; i < 10; i++) {
    spiSend(0XFF);
    
  }

    chipSelectLow();

  // command to go idle in SPI mode
  while ((status_ = SDCARD_CardCommand(CMD0, 0)) != R1_IDLE_STATE) {
    unsigned int d = millis() - t0;
    if (d > SD_INIT_TIMEOUT) {
      error(SD_CARD_ERROR_CMD0);
      goto fail;
    }
  }
  // check SD version
  if ((SDCARD_CardCommand(CMD8, 0x1AA) & R1_ILLEGAL_COMMAND)) {
    type(SD_CARD_TYPE_SD1);
  } else {
    // only need last byte of r7 response
    for (uint8_t i = 0; i < 4; i++) {
      status_ = spiRec();
    }
    if (status_ != 0XAA) {
      error(SD_CARD_ERROR_CMD8);
      goto fail;
    }
    type(SD_CARD_TYPE_SD2);
  }

  // initialize card and send host supports SDHC if SD2
  arg = get_type() == SD_CARD_TYPE_SD2 ? 0X40000000 : 0;

  while ((status_ = cardAcmd(ACMD41, arg)) != R1_READY_STATE) {
    // check for timeout
    unsigned int d = millis() - t0;
    if (d > SD_INIT_TIMEOUT) {
      error(SD_CARD_ERROR_ACMD41);
      goto fail;
    }
  }
  // if SD2 read OCR register to check for SDHC card
  if (get_type() == SD_CARD_TYPE_SD2) {
    if (SDCARD_CardCommand(CMD58, 0)) {
      error(SD_CARD_ERROR_CMD58);
      goto fail;
    }
    if ((spiRec() & 0XC0) == 0XC0) {
      type(SD_CARD_TYPE_SDHC);
    }
    // discard rest of ocr - contains allowed voltage range
    for (uint8_t i = 0; i < 3; i++) {
      spiRec();
    }
  }
  chipSelectHigh();

  #ifndef SOFTWARE_SPI
  return setSckRate(sckRateID);
  #else  // SOFTWARE_SPI
  return SD_SUCCESS;
  #endif  // SOFTWARE_SPI
fail:
  chipSelectHigh();
  return SD_ERROR;
}

//------------------------------------------------------------------------------
static uint8_t chip_select_asserted = 0;

void chipSelectHigh(void) 
{
  digitalWrite(chipSelectPin_, HIGH);
  if (chip_select_asserted) {
    chip_select_asserted = 0;
    // SDCARD_SPI.endTransaction();
  }
}
//------------------------------------------------------------------------------
void chipSelectLow(void) 
{
  #ifdef USE_SPI_LIB
  if (!chip_select_asserted) {
    chip_select_asserted = 1;
    SPI_BeginTransaction(settings);
  }
  #endif
  digitalWrite(chipSelectPin_, LOW);
}
//------------------------------------------------------------------------------
// send command and return error code.  Return zero for OK
uint8_t SDCARD_CardCommand(uint8_t cmd, uint32_t arg) 
{
  // end read if in partialBlockRead mode
  readEnd();

  // select card
  chipSelectLow();

  // wait up to 300 ms if busy
  waitNotBusy(300);

  // send command
  spiSend(cmd | 0x40);

  // send argument
  for (int8_t s = 24; s >= 0; s -= 8) {
    spiSend(arg >> s);
  }

  // send CRC
  uint8_t crc = 0XFF;
  if (cmd == CMD0) {
    crc = 0X95;  // correct crc for CMD0 with arg 0
  }
  if (cmd == CMD8) {
    crc = 0X87;  // correct crc for CMD8 with arg 0X1AA
  }
  spiSend(crc);

  // wait for response
  for (uint8_t i = 0; ((status_ = spiRec()) & 0X80) && i != 0XFF; i++)
    ;
  return status_;
}
//------------------------------------------------------------------------------
// set the SPI clock frequency
uint8_t SDCARD_SetSpiClock(uint32_t clock) 
{
  settings = SPI_settings(clock, MSBFIRST, SPI_MODE0);
  return true;
}
//------------------------------------------------------------------------------
/** Skip remaining data in a block when in partial block read mode. */
static void readEnd(void) 
{
  if (inBlock_) {
    // skip data and crc
    #ifdef OPTIMIZE_HARDWARE_SPI
    // optimize skip for hardware
    SPDR = 0XFF;
    while (offset_++ < 513) {
      while (!(SPSR & (1 << SPIF)))
        ;
      SPDR = 0XFF;
    }
    // wait for last crc byte
    while (!(SPSR & (1 << SPIF)))
      ;
    #else  // OPTIMIZE_HARDWARE_SPI
    while (offset_++ < 514) {
      spiRec();
    }
    #endif  // OPTIMIZE_HARDWARE_SPI
    chipSelectHigh();
    inBlock_ = 0;
  }
}
//------------------------------------------------------------------------------

/* PRIVATES */
// wait for card to go not busy
static uint8_t waitNotBusy(unsigned int timeoutMillis) 
{
  unsigned int t0 = millis();
  unsigned int d;
  do {
    if (spiRec() == 0XFF) {
      return true;
    }
    d = millis() - t0;
  } while (d < timeoutMillis);
  return false;
}
//------------------------------------------------------------------------------
static uint8_t cardAcmd(uint8_t cmd, uint32_t arg) 
{
    SDCARD_CardCommand(CMD55, 0);
    return SDCARD_CardCommand(cmd, arg);
}
static void spiSend(uint8_t b) 
{
  #ifndef USE_SPI_LIB
  SPDR = b;
  while (!(SPSR & (1 << SPIF)))
    ;
  #else
  SPI_transfer(b);
  #endif
}
/** Receive a byte from the card */
static uint8_t spiRec(void) 
{
  #ifndef USE_SPI_LIB
  spiSend(0XFF);
  return SPDR;
  #else
  return SPI_transfer(0xFF);
  #endif
}

static void type(uint8_t value) 
{
    type_ = value;
}

static uint8_t get_type() 
{
    return type_;
}

static void error(uint8_t code) 
{
    errorCode_ = code;
}

static uint8_t setSckRate(uint8_t sckRateID) 
{
  if (sckRateID > 6) {
    error(SD_CARD_ERROR_SCK_RATE);
    return false;
  }
  #ifndef USE_SPI_LIB
  // see avr processor datasheet for SPI register bit definitions
  if ((sckRateID & 1) || sckRateID == 6) {
    SPSR &= ~(1 << SPI2X);
  } else {
    SPSR |= (1 << SPI2X);
  }
  SPCR &= ~((1 << SPR1) | (1 << SPR0));
  SPCR |= (sckRateID & 4 ? (1 << SPR1) : 0)
          | (sckRateID & 2 ? (1 << SPR0) : 0);
  #else // USE_SPI_LIB
  switch (sckRateID) {
    case 0:  settings = SPI_settings(25000000, MSBFIRST, SPI_MODE0); break;
    case 1:  settings = SPI_settings(4000000, MSBFIRST, SPI_MODE0); break;
    case 2:  settings = SPI_settings(2000000, MSBFIRST, SPI_MODE0); break;
    case 3:  settings = SPI_settings(1000000, MSBFIRST, SPI_MODE0); break;
    case 4:  settings = SPI_settings(500000, MSBFIRST, SPI_MODE0); break;
    case 5:  settings = SPI_settings(250000, MSBFIRST, SPI_MODE0); break;
    default: settings = SPI_settings(125000, MSBFIRST, SPI_MODE0);
  }
  #endif // USE_SPI_LIB
  return SD_SUCCESS;
}
