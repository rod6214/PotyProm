#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "spi.h"
#include "arduino_generics.h"

static int initialized = 0;
/*******************************************************************************
*   spi.c v1 - 11/02/2018
        Initial definitions
*   spi.c v2 - 11/07/2018
        Updated initialization functions
*******************************************************************************/

void SPI_init(SPISettings_t settings)
{
    // // set CS, MOSI and SCK to output
    // DDR_SPI |= (1 << CS) | (1 << MOSI) | (1 << SCK);

    // // enable pull up resistor in MISO
    // DDR_SPI |= (1 << MISO);

    // // set SPI params
    // SPCR |= ((uint8_t) (initParams >> 8)) | (1 << SPE);
    // SPSR |= ((uint8_t) initParams);
}

uint8_t SPI_transfer(uint8_t data)
{
     SPDR = data;
    /*
     * The following NOP introduces a small delay that can prevent the wait
     * loop form iterating when running at the maximum speed. This gives
     * about 10% more speed, even if it seems counter-intuitive. At lower
     * speeds it is unnoticed.
     */
    asm volatile("nop");
    while (!(SPSR & _BV(SPIF))) ; // wait
    return SPDR;
}

void SPI_transfer_Bytes(void *buf, size_t count)
{
     if (count == 0) return;
    uint8_t *p = (uint8_t *)buf;
    SPDR = *p;
    while (--count > 0) {
      uint8_t out = *(p + 1);
      while (!(SPSR & _BV(SPIF))) ;
      uint8_t in = SPDR;
      SPDR = out;
      *p++ = in;
    }
    while (!(SPSR & _BV(SPIF))) ;
    *p = SPDR;
}

void SPI_begin()
{
  uint8_t sreg = SREG;
  noInterrupts(); // Protect from a scheduler and prevent transactionBegin
  if (!initialized) {
    // Set SS to high so a connected chip will be "deselected" by default

    //Note: This is only for arduino to map real port numbers
    // uint8_t port = digitalPinToPort(SS);
    // uint8_t bit = digitalPinToBitMask(SS);
    // volatile uint8_t *reg = portModeRegister(port);
    uint8_t bit = (1<<SS);
    volatile uint8_t *reg = &PORTB;
    // if the SS pin is not already configured as an output
    // then set it high (to enable the internal pull-up resistor)
    if(!(*reg & bit)){
      digitalWrite(bit, HIGH);
    }

    // When the SS pin is set as OUTPUT, it can be used as
    // a general purpose output port (it doesn't influence
    // SPI operations).
    pinMode(bit, OUTPUT);

    // Warning: if the SS pin ever becomes a LOW INPUT then SPI
    // automatically switches to Slave, so the data direction of
    // the SS pin MUST be kept as OUTPUT.
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);

    // Set direction register for SCK and MOSI pin.
    // MISO pin automatically overrides to INPUT.
    // By doing this AFTER enabling SPI, we avoid accidentally
    // clocking in a single bit since the lines go directly
    // from "input" to SPI control.
    // http://code.google.com/p/arduino/issues/detail?id=888
    pinMode((1<<SCK), OUTPUT);
    pinMode((1<<MOSI), OUTPUT);
  }
  initialized++; // reference count
  SREG = sreg;
}

void SPI_BeginTransaction(SPISettings_t settings) 
{
    SPCR = settings.spcr;
    SPSR = settings.spsr;
}

SPISettings_t SPI_settings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)     
{
    // Clock settings are defined as follows. Note that this shows SPI2X
    // inverted, so the bits form increasing numbers. Also note that
    // fosc/64 appears twice
    // SPR1 SPR0 ~SPI2X Freq
    //   0    0     0   fosc/2
    //   0    0     1   fosc/4
    //   0    1     0   fosc/8
    //   0    1     1   fosc/16
    //   1    0     0   fosc/32
    //   1    0     1   fosc/64
    //   1    1     0   fosc/64
    //   1    1     1   fosc/128

    // We find the fastest clock that is less than or equal to the
    // given clock rate. The clock divider that results in clock_setting
    // is 2 ^^ (clock_div + 1). If nothing is slow enough, we'll use the
    // slowest (128 == 2 ^^ 7, so clock_div = 6).
    uint8_t clockDiv;
    SPISettings_t settings;
    // When the clock is known at compile time, use this if-then-else
    // cascade, which the compiler knows how to completely optimize
    // away. When clock is not known, use a loop instead, which generates
    // shorter code.
    if (__builtin_constant_p(clock)) {
      if (clock >= F_CPU / 2) {
        clockDiv = 0;
      } else if (clock >= F_CPU / 4) {
        clockDiv = 1;
      } else if (clock >= F_CPU / 8) {
        clockDiv = 2;
      } else if (clock >= F_CPU / 16) {
        clockDiv = 3;
      } else if (clock >= F_CPU / 32) {
        clockDiv = 4;
      } else if (clock >= F_CPU / 64) {
        clockDiv = 5;
      } else {
        clockDiv = 6;
      }
    } else {
      uint32_t clockSetting = F_CPU / 2;
      clockDiv = 0;
      while (clockDiv < 6 && clock < clockSetting) {
        clockSetting /= 2;
        clockDiv++;
      }
    }

    // Compensate for the duplicate fosc/64
    if (clockDiv == 6)
    clockDiv = 7;

    // Invert the SPI2X bit
    clockDiv ^= 0x1;

    // Pack into the SPISettings class
    settings.spcr = _BV(SPE) | _BV(MSTR) | ((bitOrder == LSBFIRST) ? _BV(DORD) : 0) |
      (dataMode & SPI_MODE_MASK) | ((clockDiv >> 1) & SPI_CLOCK_MASK);
    settings.spsr = clockDiv & SPI_2XCLOCK_MASK;
    return settings;
}

// PRIVATES

