add_avr_executable(SDCardDriver main.cpp)

avr_target_link_libraries(SDCardDriver lCRC lSD lsdcard lspi lports lwiring)
