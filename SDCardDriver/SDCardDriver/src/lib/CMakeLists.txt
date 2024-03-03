enable_language(C ASM)

add_avr_library(
   lCRC
   CRC.s
)

add_avr_library(
   lsdcard
   sdcard.c
)

add_avr_library(
   lspi
   spi.c
)

add_avr_library(
   lports
   ports.c
)

add_avr_library(
   lwiring
   wiring.c
)

add_avr_library(
   lSD
   File.cpp
   SD.cpp
   SdVolume.cpp
   SdFile.cpp
   Sd2Card.cpp
   Stream.cpp
   Print.cpp
   
)
