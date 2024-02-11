

add_avr_executable(ExtraPortyController main.c)
# add_avr_executable(MemoryController main.asm)

# avr_target_link_libraries(MemoryController entry)
avr_target_link_libraries(ExtraPortyController eeprom i2c 595_driver)
# avr_target_link_libraries(MemoryController ext_eeprom_mem io_mem io_uart ports)
