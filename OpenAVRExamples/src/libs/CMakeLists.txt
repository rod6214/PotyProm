# enable_language(C ASM)
# set_property(SOURCE test.s APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")
add_avr_library(
   libs
   test.c
)