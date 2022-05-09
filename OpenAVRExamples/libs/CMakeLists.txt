# enable_language(C ASM)
# set_property(SOURCE test.s APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")
add_library(
   libs
   test.c
   test.h
)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)
