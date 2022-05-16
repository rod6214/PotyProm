add_avr_executable(LogicAnalyzer mainTest.c)

avr_target_link_libraries(LogicAnalyzer io_ports startup serial io_uart)
