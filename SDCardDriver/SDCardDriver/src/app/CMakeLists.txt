

add_avr_executable(SDCardDriver main.c)

avr_target_link_libraries(SDCardDriver CRC spi sdcard)
