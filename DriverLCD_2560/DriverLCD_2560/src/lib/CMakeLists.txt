enable_language(C ASM)

add_avr_library(
   ext_eeprom_mem
   ext_eeprom_mem.c
   ext_eeprom_mem.h
)

add_avr_library(
   io_mem
   io_mem.c
   io_mem.h
)

add_avr_library(
   io_uart
   io_uart.c
   io_uart.h
)

add_avr_library(
   lcd_driver
   lcd_driver.c
   lcd_driver.h
)
