

add_avr_executable(LCD_Driver main.c interrupts.c)

avr_target_link_libraries(LCD_Driver ext_eeprom_mem io_mem io_uart lcd_driver)
