

add_avr_executable(MemoryController main.c)

avr_target_link_libraries(MemoryController sddriver fat32 spi)
# avr_target_link_libraries(MemoryController ext_eeprom_mem io_mem io_uart ports)
