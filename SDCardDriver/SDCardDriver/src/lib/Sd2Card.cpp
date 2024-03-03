/* Arduino Sd2Card Library
   Copyright (C) 2009 by William Greiman

   This file is part of the Arduino Sd2Card Library

   This Library is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the Arduino Sd2Card Library.  If not, see
   <http://www.gnu.org/licenses/>.
*/
#define USE_SPI_LIB
#include "arduino_generics.h"
#include "Sd2Card.h"
#include "sdcard.h"
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// send command and return error code.  Return zero for OK
uint8_t Sd2Card::cardCommand(uint8_t cmd, uint32_t arg) 
{
  return 0;
}
//------------------------------------------------------------------------------
/**
   Determine the size of an SD flash memory card.

   \return The number of 512 byte data blocks in the card
           or zero if an error occurs.
*/
uint32_t Sd2Card::cardSize(void) 
{
    return 0;
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
uint8_t Sd2Card::erase(uint32_t firstBlock, uint32_t lastBlock) 
{
  return false;
}
//------------------------------------------------------------------------------
/** Determine if card supports single block erase.

   \return The value one, true, is returned if single block erase is supported.
   The value zero, false, is returned if single block erase is not supported.
*/
uint8_t Sd2Card::eraseSingleBlockEnable(void) 
{
    return 0;
}
//------------------------------------------------------------------------------
/**
   Initialize an SD flash memory card.

   \param[in] sckRateID SPI clock rate selector. See setSckRate().
   \param[in] chipSelectPin SD chip select pin number.

   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.  The reason for failure
   can be determined by calling errorCode() and errorData().
*/
uint8_t Sd2Card::init(uint8_t sckRateID, uint8_t chipSelectPin) 
{
  return !SDCARD_init(sckRateID, chipSelectPin);
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
void Sd2Card::partialBlockRead(uint8_t value) 
{
  SDCARD_partialBlockRead(value);
}
//------------------------------------------------------------------------------
/**
   Read a 512 byte block from an SD card device.

   \param[in] block Logical block to be read.
   \param[out] dst Pointer to the location that will receive the data.

   \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t Sd2Card::readBlock(uint32_t block, uint8_t* dst) {
  return !SDCARD_readBlock(block, dst);
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
uint8_t Sd2Card::readData(uint32_t block,
                          uint16_t offset, uint16_t count, uint8_t* dst) 
{
  return !SDCARD_readData(block, offset, count, dst);
}
//------------------------------------------------------------------------------
/** Skip remaining data in a block when in partial block read mode. */
void Sd2Card::readEnd(void) 
{
  SDCARD_readEnd();
}
//------------------------------------------------------------------------------
/** read CID or CSR register */
uint8_t Sd2Card::readRegister(uint8_t cmd, void* buf) 
{
  return !SDCARD_readRegister(cmd, buf);
}
//------------------------------------------------------------------------------
/**
   Set the SPI clock rate.

   \param[in] sckRateID A value in the range [0, 6].

   The SPI clock will be set to F_CPU/pow(2, 1 + sckRateID). The maximum
   SPI rate is F_CPU/2 for \a sckRateID = 0 and the minimum rate is F_CPU/128
   for \a scsRateID = 6.

   \return The value one, true, is returned for success and the value zero,
   false, is returned for an invalid value of \a sckRateID.
*/
uint8_t Sd2Card::setSckRate(uint8_t sckRateID) 
{
  return !SDCARD_setSckRate(sckRateID);
}
#ifdef USE_SPI_LIB
//------------------------------------------------------------------------------
// set the SPI clock frequency
uint8_t Sd2Card::setSpiClock(uint32_t clock) 
{
  return !SDCARD_SetSpiClock(clock);
}
#endif
//------------------------------------------------------------------------------
// wait for card to go not busy
uint8_t Sd2Card::waitNotBusy(unsigned int timeoutMillis)
{
  return !SDCARD_waitNotBusy(timeoutMillis);
}
//------------------------------------------------------------------------------
/** Wait for start block token */
uint8_t Sd2Card::waitStartBlock(void) 
{
  return !SDCARD_waitStartBlock();
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
uint8_t Sd2Card::writeBlock(uint32_t blockNumber, const uint8_t* src, uint8_t blocking) 
{
  return !SDCARD_writeBlock(blockNumber, src, blocking);
}
//------------------------------------------------------------------------------
/** Write one data block in a multiple block write sequence */
uint8_t Sd2Card::writeData(const uint8_t* src) 
{
  // wait for previous write to finish
  return !SDCARD_writeData(src);
}
//------------------------------------------------------------------------------
// send one block of data for write block or write multiple blocks
uint8_t Sd2Card::writeData(uint8_t token, const uint8_t* src) 
{
  return !SDCARD_writeData2(token, src) ;
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
uint8_t Sd2Card::writeStart(uint32_t blockNumber, uint32_t eraseCount) 
{
    return !SDCARD_writeStart(blockNumber, eraseCount);
}
//------------------------------------------------------------------------------
/** End a write multiple blocks sequence.

  \return The value one, true, is returned for success and
   the value zero, false, is returned for failure.
*/
uint8_t Sd2Card::writeStop(void) 
{
    return !SDCARD_writeStop();
}
//------------------------------------------------------------------------------
/** Check if the SD card is busy

  \return The value one, true, is returned when is busy and
   the value zero, false, is returned for when is NOT busy.
*/
uint8_t Sd2Card::isBusy(void) 
{
    return !SDCARD_isBusy();
}
