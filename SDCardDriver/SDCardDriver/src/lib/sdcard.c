#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "sdcard.h"
#include "arduino_generics.h"
#include "wiring.h"
#include "spi.h"
#include "SdInfo.h"

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
static uint8_t readRegister(uint8_t cmd, void* buf);
static uint8_t readCSD(csd_t* csd);
static uint8_t readRegister(uint8_t cmd, void* buf);
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
  return SD_SUCCESS;
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
/** Erase a range of blocks.

   \param[in] firstBlock The address of the first block in the range.
   \param[in] lastBlock The address of the last block in the range.

   \note This function requests the SD card to do a flash erase for a
   range of blocks.  The data on the card after an erase operation is
   either 0 or 1, depends on the card vendor.  The card must support
   single block erase.

   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t SDCARD_erase(uint32_t firstBlock, uint32_t lastBlock) {
  if (!SDCARD_eraseSingleBlockEnable()) {
    error(SD_CARD_ERROR_ERASE_SINGLE_BLOCK);
    goto fail;
  }
  if (type_ != SD_CARD_TYPE_SDHC) {
    firstBlock <<= 9;
    lastBlock <<= 9;
  }
  if (SDCARD_CardCommand(CMD32, firstBlock)
      || SDCARD_CardCommand(CMD33, lastBlock)
      || SDCARD_CardCommand(CMD38, 0)) {
    error(SD_CARD_ERROR_ERASE);
    goto fail;
  }
  if (!waitNotBusy(SD_ERASE_TIMEOUT)) {
    error(SD_CARD_ERROR_ERASE_TIMEOUT);
    goto fail;
  }
  chipSelectHigh();
  return SD_SUCCESS;

fail:
  chipSelectHigh();
  return SD_ERROR;
}
//------------------------------------------------------------------------------
/** Wait for start block token */
uint8_t SDCARD_waitStartBlock(void) {
  unsigned int t0 = millis();
  while ((status_ = spiRec()) == 0XFF) {
    unsigned int d = millis() - t0;
    if (d > SD_READ_TIMEOUT) {
      error(SD_CARD_ERROR_READ_TIMEOUT);
      goto fail;
    }
  }
  if (status_ != DATA_START_BLOCK) {
    error(SD_CARD_ERROR_READ);
    goto fail;
  }
  return SD_SUCCESS;

fail:
  chipSelectHigh();
  return SD_ERROR;
}
//------------------------------------------------------------------------------
/** Determine if card supports single block erase.

   \return The value one, true, is returned if single block erase is supported.
   The value zero, false, is returned if single block erase is not supported.
*/
uint8_t SDCARD_eraseSingleBlockEnable(void) {
  csd_t csd;
  return readCSD(&csd) ? csd.v1.erase_blk_en : 0;
}
//------------------------------------------------------------------------------
/**
   Enable or disable partial block reads.

   Enabling partial block reads improves performance by allowing a block
   to be read over the SPI bus as several sub-blocks.  Errors may occur
   if the time between reads is too long since the SD card may timeout.
   The SPI SS line will be held low until the entire block is read or
   readEnd() is called.

   Use this for applications like the Adafruit Wave Shield.

   \param[in] value The value TRUE (non-zero) or FALSE (zero).)
*/
void SDCARD_partialBlockRead(uint8_t value) {
  readEnd();
  partialBlockRead_ = value;
}
//------------------------------------------------------------------------------
/**
   Read a 512 byte block from an SD card device.

   \param[in] block Logical block to be read.
   \param[out] dst Pointer to the location that will receive the data.

   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t SDCARD_readBlock(uint32_t block, uint8_t* dst) {
  return SDCARD_readData(block, 0, 512, dst);
}
//------------------------------------------------------------------------------
/**
   Read part of a 512 byte block from an SD card.

   \param[in] block Logical block to be read.
   \param[in] offset Number of bytes to skip at start of block
   \param[out] dst Pointer to the location that will receive the data.
   \param[in] count Number of bytes to read
   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t SDCARD_readData(uint32_t block,
                          uint16_t offset, uint16_t count, uint8_t* dst) {
  if (count == 0) {
    return SD_SUCCESS;
  }
  if ((count + offset) > 512) {
    goto fail;
  }
  if (!inBlock_ || block != block_ || offset < offset_) {
    block_ = block;
    // use address if not SDHC card
    if (get_type() != SD_CARD_TYPE_SDHC) {
      block <<= 9;
    }
    if (SDCARD_CardCommand(CMD17, block)) {
      error(SD_CARD_ERROR_CMD17);
      goto fail;
    }
    if (SDCARD_waitStartBlock()) {
      goto fail;
    }
    offset_ = 0;
    inBlock_ = 1;
  }

  #ifdef OPTIMIZE_HARDWARE_SPI
  // start first spi transfer
  SPDR = 0XFF;

  // skip data before offset
  for (; offset_ < offset; offset_++) {
    while (!(SPSR & (1 << SPIF)))
      ;
    SPDR = 0XFF;
  }
  // transfer data
  n = count - 1;
  for (uint16_t i = 0; i < n; i++) {
    while (!(SPSR & (1 << SPIF)))
      ;
    dst[i] = SPDR;
    SPDR = 0XFF;
  }
  // wait for last byte
  while (!(SPSR & (1 << SPIF)))
    ;
  dst[n] = SPDR;

  #else  // OPTIMIZE_HARDWARE_SPI

  // skip data before offset
  for (; offset_ < offset; offset_++) {
    spiRec();
  }
  // transfer data
  for (uint16_t i = 0; i < count; i++) {
    dst[i] = spiRec();
  }
  #endif  // OPTIMIZE_HARDWARE_SPI

  offset_ += count;
  if (!partialBlockRead_ || offset_ >= 512) {
    // read rest of data, checksum and set chip select high
    readEnd();
  }
  return SD_SUCCESS;

fail:
PORTD = 3;
  chipSelectHigh();
  return SD_ERROR;
}
//------------------------------------------------------------------------------
/**
   Writes a 512 byte block to an SD card.

   \param[in] blockNumber Logical block to be written.
   \param[in] src Pointer to the location of the data to be written.
   \param[in] blocking If the write should be blocking.
   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t SDCARD_writeBlock(uint32_t blockNumber, const uint8_t* src, uint8_t blocking) {
  #if SD_PROTECT_BLOCK_ZERO
  // don't allow write to first block
  if (blockNumber == 0) {
    error(SD_CARD_ERROR_WRITE_BLOCK_ZERO);
    goto fail;
  }
  #endif  // SD_PROTECT_BLOCK_ZERO

  // use address if not SDHC card
  if (get_type() != SD_CARD_TYPE_SDHC) {
    blockNumber <<= 9;
  }
  if (SDCARD_CardCommand(CMD24, blockNumber)) {
    error(SD_CARD_ERROR_CMD24);
    goto fail;
  }
  if (!SDCARD_writeData2(DATA_START_BLOCK, src)) {
    goto fail;
  }
  if (blocking) {
    // wait for flash programming to complete
    if (!waitNotBusy(SD_WRITE_TIMEOUT)) {
      error(SD_CARD_ERROR_WRITE_TIMEOUT);
      goto fail;
    }
    // response is r2 so get and check two bytes for nonzero
    if (SDCARD_CardCommand(CMD13, 0) || spiRec()) {
      error(SD_CARD_ERROR_WRITE_PROGRAMMING);
      goto fail;
    }
  }
  chipSelectHigh();
  return SD_SUCCESS;

fail:
  chipSelectHigh();
  return SD_ERROR;
}

/** Write one data block in a multiple block write sequence */
uint8_t SDCARD_writeData(const uint8_t* src) {
  // wait for previous write to finish
  if (!waitNotBusy(SD_WRITE_TIMEOUT)) {
    error(SD_CARD_ERROR_WRITE_MULTIPLE);
    chipSelectHigh();
    return SD_ERROR;
  }
  return SDCARD_writeData2(WRITE_MULTIPLE_TOKEN, src);
}
//------------------------------------------------------------------------------

// send one block of data for write block or write multiple blocks
uint8_t SDCARD_writeData2(uint8_t token, const uint8_t* src) {
  #ifdef OPTIMIZE_HARDWARE_SPI

  // send data - optimized loop
  SPDR = token;

  // send two byte per iteration
  for (uint16_t i = 0; i < 512; i += 2) {
    while (!(SPSR & (1 << SPIF)))
      ;
    SPDR = src[i];
    while (!(SPSR & (1 << SPIF)))
      ;
    SPDR = src[i + 1];
  }

  // wait for last data byte
  while (!(SPSR & (1 << SPIF)))
    ;

  #else  // OPTIMIZE_HARDWARE_SPI
  spiSend(token);
  for (uint16_t i = 0; i < 512; i++) {
    spiSend(src[i]);
  }
  #endif  // OPTIMIZE_HARDWARE_SPI
  spiSend(0xff);  // dummy crc
  spiSend(0xff);  // dummy crc

  status_ = spiRec();
  if ((status_ & DATA_RES_MASK) != DATA_RES_ACCEPTED) {
    error(SD_CARD_ERROR_WRITE);
    chipSelectHigh();
    return SD_ERROR;
  }
  return SD_SUCCESS;
}
//------------------------------------------------------------------------------
/** Start a write multiple blocks sequence.

   \param[in] blockNumber Address of first block in sequence.
   \param[in] eraseCount The number of blocks to be pre-erased.

   \note This function is used with writeData() and writeStop()
   for optimized multiple block writes.

   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t SDCARD_writeStart(uint32_t blockNumber, uint32_t eraseCount) {
  #if SD_PROTECT_BLOCK_ZERO
  // don't allow write to first block
  if (blockNumber == 0) {
    error(SD_CARD_ERROR_WRITE_BLOCK_ZERO);
    goto fail;
  }
  #endif  // SD_PROTECT_BLOCK_ZERO
  // send pre-erase count
  if (cardAcmd(ACMD23, eraseCount)) {
    error(SD_CARD_ERROR_ACMD23);
    goto fail;
  }
  // use address if not SDHC card
  if (get_type() != SD_CARD_TYPE_SDHC) {
    blockNumber <<= 9;
  }
  if (SDCARD_CardCommand(CMD25, blockNumber)) {
    error(SD_CARD_ERROR_CMD25);
    goto fail;
  }
  return SD_SUCCESS;

fail:
  chipSelectHigh();
  return SD_ERROR;
}
//------------------------------------------------------------------------------
/** End a write multiple blocks sequence.

  \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t SDCARD_writeStop(void) {
  if (!waitNotBusy(SD_WRITE_TIMEOUT)) {
    goto fail;
  }
  spiSend(STOP_TRAN_TOKEN);
  if (!waitNotBusy(SD_WRITE_TIMEOUT)) {
    goto fail;
  }
  chipSelectHigh();
  return SD_SUCCESS;

fail:
  error(SD_CARD_ERROR_STOP_TRAN);
  chipSelectHigh();
  return SD_ERROR;
}
//------------------------------------------------------------------------------
/** Check if the SD card is busy

  \return The value one, true, is returned when is busy and
   the value zero, false, is returned for when is NOT busy.
*/
uint8_t SDCARD_isBusy(void) {
  chipSelectLow();
  uint8_t b = spiRec();
  chipSelectHigh();

  return (b != 0XFF);
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
      return SD_SUCCESS;
    }
    d = millis() - t0;
  } while (d < timeoutMillis);
  return SD_ERROR;
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
    return SD_ERROR;
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

static uint8_t readCSD(csd_t* csd) {
  return readRegister(CMD9, csd);
}

/** read CID or CSR register */
static uint8_t readRegister(uint8_t cmd, void* buf) {
  uint8_t* dst = (uint8_t*)(buf);
  if (SDCARD_CardCommand(cmd, 0)) {
    error(SD_CARD_ERROR_READ_REG);
    goto fail;
  }
  if (!SDCARD_waitStartBlock()) {
    goto fail;
  }
  // transfer data
  for (uint16_t i = 0; i < 16; i++) {
    dst[i] = spiRec();
  }
  spiRec();  // get first crc byte
  spiRec();  // get second crc byte
  chipSelectHigh();
  return SD_SUCCESS;

fail:
  chipSelectHigh();
  return SD_ERROR;
}
//------------------------------------------------------------------------------
