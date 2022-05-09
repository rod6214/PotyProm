find_program(AVR_CC avr-gcc REQUIRED)
find_program(AVR_CXX avr-g++ REQUIRED)
find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_SIZE_TOOL avr-size REQUIRED)
find_program(AVR_OBJDUMP avr-objdump REQUIRED)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})

function(add_avr_executable EXECUTABLE_NAME)
    if(NOT ARGN)
        message(FATAL_ERROR "No source files given for ${EXECUTABLE_NAME}.")
    endif(NOT ARGN)

    if(NOT AVR_MCU)
        message(FATAL_ERROR "It is necessary to configure the variable AVR_MCU.")
    endif(NOT AVR_MCU)

    # set file names
    set(elf_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.elf)
    set(hex_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.hex)
    set(lst_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.lst)
    set(map_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.map)
    set(eeprom_image ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}-eeprom.hex)

    set (${EXECUTABLE_NAME}_ELF_TARGET ${elf_file} PARENT_SCOPE)
    set (${EXECUTABLE_NAME}_HEX_TARGET ${hex_file} PARENT_SCOPE)
    set (${EXECUTABLE_NAME}_LST_TARGET ${lst_file} PARENT_SCOPE)
    set (${EXECUTABLE_NAME}_MAP_TARGET ${map_file} PARENT_SCOPE)
    set (${EXECUTABLE_NAME}_EEPROM_TARGET ${eeprom_file} PARENT_SCOPE)
    # elf file
    add_executable(${elf_file} EXCLUDE_FROM_ALL ${ARGN})

    set_target_properties(
        ${elf_file}
        PROPERTIES
        COMPILE_FLAGS "-mmcu=${AVR_MCU}"
        LINK_FLAGS "-mmcu=${AVR_MCU} -Wl,--gc-sections -mrelax -Wl,-Map,${map_file}"
    )

    add_custom_command(
        OUTPUT ${hex_file}
        COMMAND
        ${AVR_OBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}
        COMMAND
        ${AVR_SIZE_TOOL} ${AVR_SIZE_ARGS} ${elf_file}
        DEPENDS ${elf_file}
    )

    add_custom_command(
        OUTPUT ${lst_file}
        COMMAND
        ${AVR_OBJDUMP} -d ${elf_file} > ${lst_file}
        DEPENDS ${elf_file}
    )

    # eeprom
    add_custom_command(
        OUTPUT ${eeprom_image}
        COMMAND
        ${AVR_OBJCOPY} -j .eeprom --set-section-flags=.eeprom=alloc,load
            --change-section-lma .eeprom=0 --no-change-warnings
            -O ihex ${elf_file} ${eeprom_image}
        DEPENDS ${elf_file}
    )

    add_custom_target(
        ${EXECUTABLE_NAME}
        ALL
        DEPENDS ${hex_file} ${lst_file} ${eeprom_image}
    )

    set_target_properties(
        ${EXECUTABLE_NAME}
        PROPERTIES
        OUTPUT_NAME "${elf_file}"
    )

    # clean
    get_directory_property(clean_files ADDITIONAL_MAKE_CLEAN_FILES)
        set_directory_properties(
        PROPERTIES
        ADDITIONAL_MAKE_CLEAN_FILES "${map_file}"
    )

    # upload - with avrdude
    add_custom_target(
        upload_${EXECUTABLE_NAME}
        ${AVR_UPLOADTOOL} ${AVR_UPLOADTOOL_BASE_OPTIONS} ${AVR_UPLOADTOOL_OPTIONS}
        -U flash:w:${hex_file}
        -P ${AVR_UPLOADTOOL_PORT}
        DEPENDS ${hex_file}
        COMMENT "Uploading ${hex_file} to ${AVR_MCU} using ${AVR_PROGRAMMER}"
    )

    # upload eeprom only - with avrdude
    # see also bug http://savannah.nongnu.org/bugs/?40142
    add_custom_target(
        upload_${EXECUTABLE_NAME}_eeprom
        ${AVR_UPLOADTOOL} ${AVR_UPLOADTOOL_BASE_OPTIONS} ${AVR_UPLOADTOOL_OPTIONS}
        -U eeprom:w:${eeprom_image}
        -P ${AVR_UPLOADTOOL_PORT}
        DEPENDS ${eeprom_image}
        COMMENT "Uploading ${eeprom_image} to ${AVR_MCU} using ${AVR_PROGRAMMER}"
    )

    # disassemble
    add_custom_target(
        disassemble_${EXECUTABLE_NAME}
        ${AVR_OBJDUMP} -h -S ${elf_file} > ${EXECUTABLE_NAME}.lst
        DEPENDS ${elf_file}
    )
endfunction(add_avr_executable)

##########################################################################
# add_avr_library
# - IN_VAR: LIBRARY_NAME
#
# Calls add_library with an optionally concatenated name
# <LIBRARY_NAME>${MCU_TYPE_FOR_FILENAME}.
# This needs to be used for linking against the library, e.g. calling
# target_link_libraries(...).
##########################################################################
function(add_avr_library LIBRARY_NAME)
    if(NOT ARGN)
        message(FATAL_ERROR "No source files given for ${LIBRARY_NAME}.")
    endif(NOT ARGN)

    if(NOT AVR_MCU)
        message(FATAL_ERROR "It is necessary to configure the variable AVR_MCU.")
    endif(NOT AVR_MCU)

    set(lib_file ${LIBRARY_NAME}${MCU_TYPE_FOR_FILENAME})
    set (${LIBRARY_NAME}_LIB_TARGET ${elf_file} PARENT_SCOPE)

    add_library(${lib_file} STATIC ${ARGN})

    set_target_properties(
            ${lib_file}
            PROPERTIES
            COMPILE_FLAGS "-mmcu=${AVR_MCU}"
            OUTPUT_NAME "${lib_file}"
    )

    if(NOT TARGET ${LIBRARY_NAME})
        add_custom_target(
                ${LIBRARY_NAME}
                ALL
                DEPENDS ${lib_file}
        )

        set_target_properties(
                ${LIBRARY_NAME}
                PROPERTIES
                OUTPUT_NAME "${lib_file}"
        )
    endif(NOT TARGET ${LIBRARY_NAME})

endfunction(add_avr_library)

##########################################################################
# avr_target_link_libraries
# - IN_VAR: EXECUTABLE_TARGET
# - ARGN  : targets and files to link to
#
# Calls target_link_libraries with AVR target names (concatenation,
# extensions and so on.
##########################################################################
function(avr_target_link_libraries EXECUTABLE_TARGET)
   if(NOT ARGN)
      message(FATAL_ERROR "Nothing to link to ${EXECUTABLE_TARGET}.")
   endif(NOT ARGN)

   if(NOT AVR_MCU)
        message(FATAL_ERROR "It is necessary to configure the variable AVR_MCU.")
    endif(NOT AVR_MCU)

   get_target_property(TARGET_LIST ${EXECUTABLE_TARGET} OUTPUT_NAME)

   foreach(TGT ${ARGN})
      if(TARGET ${TGT})
         get_target_property(ARG_NAME ${TGT} OUTPUT_NAME)
         list(APPEND NON_TARGET_LIST ${ARG_NAME})
      else(TARGET ${TGT})
         list(APPEND NON_TARGET_LIST ${TGT})
      endif(TARGET ${TGT})
   endforeach(TGT ${ARGN})

   target_link_libraries(${TARGET_LIST} ${NON_TARGET_LIST})
endfunction(avr_target_link_libraries EXECUTABLE_TARGET)

##########################################################################
# avr_target_include_directories
#
# Calls target_include_directories with AVR target names
##########################################################################

function(avr_target_include_directories EXECUTABLE_TARGET)
    if(NOT ARGN)
        message(FATAL_ERROR "No include directories to add to ${EXECUTABLE_TARGET}.")
    endif()

    get_target_property(TARGET_LIST ${EXECUTABLE_TARGET} OUTPUT_NAME)
    set(extra_args ${ARGN})

    target_include_directories(${TARGET_LIST} ${extra_args})
endfunction()

##########################################################################
# avr_target_compile_definitions
#
# Calls target_compile_definitions with AVR target names
##########################################################################

function(avr_target_compile_definitions EXECUTABLE_TARGET)
    if(NOT ARGN)
        message(FATAL_ERROR "No compile definitions to add to ${EXECUTABLE_TARGET}.")
    endif()

    get_target_property(TARGET_LIST ${EXECUTABLE_TARGET} OUTPUT_NAME)
    set(extra_args ${ARGN})

   target_compile_definitions(${TARGET_LIST} ${extra_args})
endfunction()

function(avr_generate_fixed_targets)
    if(NOT AVR_MCU)
        message(FATAL_ERROR "It is necessary to configure the variable AVR_MCU.")
    endif(NOT AVR_MCU)

   # get status
   add_custom_target(
      get_status
      ${AVR_UPLOADTOOL} ${AVR_UPLOADTOOL_BASE_OPTIONS} -P ${AVR_UPLOADTOOL_PORT} -n -v
      COMMENT "Get status from ${AVR_MCU}"
   )
   
   # get fuses
   add_custom_target(
      get_fuses
      ${AVR_UPLOADTOOL} ${AVR_UPLOADTOOL_BASE_OPTIONS} -P ${AVR_UPLOADTOOL_PORT} -n
         -U lfuse:r:-:b
         -U hfuse:r:-:b
      COMMENT "Get fuses from ${AVR_MCU}"
   )
   
   # set fuses
   add_custom_target(
      set_fuses
      ${AVR_UPLOADTOOL} ${AVR_UPLOADTOOL_BASE_OPTIONS} -P ${AVR_UPLOADTOOL_PORT}
         -U lfuse:w:${AVR_L_FUSE}:m
         -U hfuse:w:${AVR_H_FUSE}:m
         COMMENT "Setup: High Fuse: ${AVR_H_FUSE} Low Fuse: ${AVR_L_FUSE}"
   )
   
   # get oscillator calibration
   add_custom_target(
      get_calibration
         ${AVR_UPLOADTOOL} ${AVR_UPLOADTOOL_BASE_OPTIONS} -P ${AVR_UPLOADTOOL_PORT}
         -U calibration:r:${AVR_MCU}_calib.tmp:r
         COMMENT "Write calibration status of internal oscillator to ${AVR_MCU}_calib.tmp."
   )
   
   # set oscillator calibration
   add_custom_target(
      set_calibration
      ${AVR_UPLOADTOOL} ${AVR_UPLOADTOOL_BASE_OPTIONS} -P ${AVR_UPLOADTOOL_PORT}
         -U calibration:w:${AVR_MCU}_calib.hex
         COMMENT "Program calibration status of internal oscillator from ${AVR_MCU}_calib.hex."
   )
endfunction()

##########################################################################
# Bypass the link step in CMake's "compiler sanity test" check
#
# CMake throws in a try_compile() target test in some generators, but does
# not know that this is a cross compiler so the executable can't link.
# Change the target type:
#
# https://stackoverflow.com/q/53633705
##########################################################################

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")