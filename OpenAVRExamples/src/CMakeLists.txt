set(AVR-EXAMPLE_SOURCE_DIR "C:/Develop/RomProgrammer/OpenAVRExamples/src")

include_directories(${AVR-EXAMPLE_SOURCE_DIR}/libs)

add_subdirectory(libs)

add_avr_executable(OpenProgrammer main.c)

avr_target_link_libraries(OpenProgrammer libs)
