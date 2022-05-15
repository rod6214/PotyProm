add_avr_executable(LogicAnalyzer mainTest.c)

avr_target_link_libraries(LogicAnalyzer startup serial io_uart)
