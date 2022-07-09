

add_avr_executable(OpenProgrammer main.c)

avr_target_link_libraries(OpenProgrammer ext_eeprom_mem io_mem io_uart lcd)
