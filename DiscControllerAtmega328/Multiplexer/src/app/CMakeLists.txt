

add_avr_executable(DiscController main.c)

avr_target_link_libraries(DiscController ext_eeprom_mem io_mem io_uart ports)
