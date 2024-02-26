add_avr_executable(SDCardDriver main.c)

avr_target_link_libraries(SDCardDriver lCRC lsdcard lspi lports lwiring)
