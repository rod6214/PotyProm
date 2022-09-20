enable_language(C ASM)

add_avr_library(
   CRC
   CRC.s
   CRC.h
)

add_avr_library(
   sdcard
   sdcard.c
   sdcard.h
)

add_avr_library(
   spi
   spi.c
   spi.h
)
