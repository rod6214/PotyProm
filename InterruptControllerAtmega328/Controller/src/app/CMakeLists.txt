

add_avr_executable(InterruptController main.c)

avr_target_link_libraries(InterruptController eeprom i2c 595_driver)
