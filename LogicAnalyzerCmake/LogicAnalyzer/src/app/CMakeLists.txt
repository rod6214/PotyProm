

add_avr_executable(LogicAnalyzer main.c)

avr_target_link_libraries(LogicAnalyzer external_int io_ports startup serial io_uart)
