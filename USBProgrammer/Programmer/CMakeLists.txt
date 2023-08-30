cmake_minimum_required(VERSION 3.14)

set(AVR_MCU ATmega32U4)
# set(__GNUC__)

project(OpenProgrammer)

add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
# add_definitions("-Werror")
# add_definitions("-pedantic")
# add_definitions("-pedantic-errors")
add_definitions("-funsigned-char")
add_definitions("-fdata-sections")
# add_definitions("-funsigned-bitfields")
add_definitions("-ffunction-sections")
add_definitions("-Og")
add_definitions("-g2")
add_definitions("-c")
add_definitions("-MD") 
add_definitions("-MP") 
add_definitions("-MF")
add_definitions("-std=gnu99")
add_definitions("-D__GNUC__=1")

set(AVR-C_SOURCE_DIR "C:/Develop/RomProgrammer/USBProgrammer/Programmer/src")

add_subdirectory(src)
