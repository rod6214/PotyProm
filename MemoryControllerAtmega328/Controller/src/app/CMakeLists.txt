
include_directories(${I2C_DIR}/include)
include_directories(${EEPROM_DIR}/include)
include_directories(${L595_DIR}/include)
include_directories(${SD_DIR}/include)
include_directories(${SPI_DIR}/include)
# link_directories(${I2C_DIR}/lib)
# link_directories(${EEPROM_DIR}/lib)

add_avr_executable(MemoryController main.cpp)
# add_avr_executable(MemoryController main.asm)
add_avr_library(li2c ${I2C_DIR}/src/i2c.c ${I2C_DIR}/src/i2cext.c)
add_avr_library(leeprom ${EEPROM_DIR}/src/eeprom.c)
add_avr_library(l595_driver ${L595_DIR}/src/595_driver.c)
add_avr_library(lSD 
${SD_DIR}/src/File.cpp 
${SD_DIR}/src/SD.cpp 
${SD_DIR}/src/SdVolume.cpp 
${SD_DIR}/src/SdFile.cpp 
${SD_DIR}/src/Sd2Card.cpp 
${SD_DIR}/src/Stream.cpp
${SD_DIR}/src/Print.cpp
)

add_avr_library(lSDExt ${SPI_DIR}/src/spi.c ${SD_DIR}/src/wiring.c ${SD_DIR}/src/sdcard.c ${SD_DIR}/src/ports.c)
avr_target_link_libraries(MemoryController leeprom li2c l595_driver lSD lSDExt)
