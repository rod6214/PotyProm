cmake_minimum_required(VERSION 3.14)

set(AVR_MCU at90s8535)

project(foo)
# add_executable(foo foo.c)
add_avr_executable(foo foo.c)