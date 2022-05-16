enable_language(C ASM)

add_avr_library(
   serial
   serial.c
   serial.h
)

add_avr_library(
   startup
   startup.c
   startup.h
)

add_avr_library(
   io_uart
   io_uart.c
   io_uart.h
)

add_avr_library(
   io_ports
   io_ports.c
   io_ports.h
)
