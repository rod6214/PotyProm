add_subdirectory(i2c)
add_subdirectory(eeprom)
add_subdirectory(shifter)

add_avr_library(
    intports
    intports.c
)

add_avr_library(
    intel_vectors
    intel_vectors.c
)
