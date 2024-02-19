
include_directories(${I2C_DIR}/include)

add_avr_executable(ExtraPortyController main.c)

avr_target_include_directories(ExtraPortyController PUBLIC i2c)

add_avr_library(i2c ${I2C_DIR}/src/i2c.c ${I2C_DIR}/src/i2cext.c)
avr_target_link_libraries(ExtraPortyController i2c)

