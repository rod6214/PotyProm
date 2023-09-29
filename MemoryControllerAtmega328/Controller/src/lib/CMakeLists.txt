enable_language(C ASM)

# add_avr_library(
#    ext_eeprom_mem
#    ext_eeprom_mem.c
#    ext_eeprom_mem.h
# )

# add_avr_library(
#    io_mem
#    io_mem.c
#    io_mem.h
# )

# add_avr_library(
#    io_uart
#    io_uart.c
#    io_uart.h
# )

# add_avr_library(
#    ports
#    ports.c
#    ports.h
# )
# add_subdirectory(SD_Driver)
# add_subdirectory(SPI)
# add_subdirectory(FAT32)

add_avr_library(
   fat32
   FAT32/FAT32.c
)
add_avr_library(
   sddriver
   SD_Driver/SD_routines.c
)
add_avr_library(
   spi
   SPI/SPI_routines.c
)
