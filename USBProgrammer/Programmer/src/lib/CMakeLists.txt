enable_language(C ASM)

# target_include_directories(usb_task PRIVATE ${AVR-C_SOURCE_DIR}/app/conf)

# message(${AVR-C_SOURCE_DIR}/app)
# add_avr_library(
#     flash_drv
#     lib_mcu/flash/flash_drv.s
#     lib_mcu/flash/flash_drv.h
# )

add_subdirectory(usb)
add_subdirectory(i2c)
add_subdirectory(eeprom)