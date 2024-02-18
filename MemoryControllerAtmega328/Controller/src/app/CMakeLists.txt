
include_directories(${I2C_DIR}/include)
# link_directories(${I2C_DIR}/lib)
include_directories(${EEPROM_DIR}/include)
link_directories(${EEPROM_DIR}/lib)

add_avr_executable(MemoryController main.c)
# add_avr_executable(MemoryController main.asm)
add_avr_library(i2c ${I2C_DIR}/src/i2c.c ${I2C_DIR}/src/i2cext.c)
# avr_target_link_libraries(MemoryController entry)
avr_target_link_libraries(MemoryController eeprom i2c 595_driver)
# avr_target_link_libraries(MemoryController ext_eeprom_mem io_mem io_uart ports)
