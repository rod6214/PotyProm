
include_directories(${I2C_DIR}/include)
include_directories(${EEPROM_DIR}/include)
link_directories(${EEPROM_DIR}/lib)

add_avr_executable(ExtraPortyController main.c)

avr_target_include_directories(ExtraPortyController PUBLIC i2c)
avr_target_include_directories(ExtraPortyController PUBLIC eeprom)

add_avr_library(i2c ${I2C_DIR}/src/i2c.c ${I2C_DIR}/src/i2cext.c)
avr_target_link_libraries(ExtraPortyController eeprom i2c 595_driver)

