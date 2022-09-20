##
## Author:  Johannes Bruder
## License: See LICENSE.TXT file included in the project
##
##
## CMake arm-none-eabi toolchain file
##

# Append current directory to CMAKE_MODULE_PATH for making device specific cmake modules visible
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Target definition
set(CMAKE_SYSTEM_NAME  Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

#---------------------------------------------------------------------------------------
# Set toolchain paths
#---------------------------------------------------------------------------------------
set(TOOLCHAIN arm-none-eabi)
if(NOT DEFINED TOOLCHAIN_PREFIX)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(TOOLCHAIN_PREFIX "/usr")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(TOOLCHAIN_PREFIX "/usr/local")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
        message(STATUS "Please specify the TOOLCHAIN_PREFIX !\n For example: -DTOOLCHAIN_PREFIX=\"C:/Program Files/GNU Tools ARM Embedded\" ")
    else()
        set(TOOLCHAIN_PREFIX "/usr")
        message(STATUS "No TOOLCHAIN_PREFIX specified, using default: " ${TOOLCHAIN_PREFIX})
    endif()
endif()
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib)

# Set system depended extensions
if(WIN32)
    set(TOOLCHAIN_EXT ".exe" )
else()
    set(TOOLCHAIN_EXT "" )
endif()

# Perform compiler test with static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

#---------------------------------------------------------------------------------------
# Set compiler/linker flags
#---------------------------------------------------------------------------------------

# Object build options
# -O0                   No optimizations, reduce compilation time and make debugging produce the expected results.
# -mthumb               Generat thumb instructions.
# -fno-builtin          Do not use built-in functions provided by GCC.
# -Wall                 Print only standard warnings, for all use Wextra
# -ffunction-sections   Place each function item into its own section in the output file.
# -fdata-sections       Place each data item into its own section in the output file.
# -fomit-frame-pointer  Omit the frame pointer in functions that don’t need one.
# -mabi=aapcs           Defines enums to be a variable sized type.
# set(OBJECT_GEN_FLAGS "-O0 -mthumb -fno-builtin -Wall -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs")
set(OBJECT_GEN_FLAGS "-D__SAM3X8E__ -DNDEBUG -w -Og -g -ffunction-sections -fdata-sections -mlong-calls -Wall -mcpu=cortex-m3")
# set(OBJECT_GEN_FLAGS "-Wall")
# "Device_Startup/system_sam3xa.d" -MT"Device_Startup/system_sam3xa.d" -MT"Device_Startup/system_sam3xa.o" -o "Device_Startup/system_sam3xa.o" "../Device_Startup/system_sam3xa.c" 
set(CMAKE_C_FLAGS   "${OBJECT_GEN_FLAGS} -std=gnu99 " CACHE INTERNAL "C Compiler options")
set(CMAKE_LIB_C_FLAGS   "${OBJECT_GEN_FLAGS} -c -std=gnu99 " CACHE INTERNAL "C Compiler options")
# set(CMAKE_C_FLAGS "--std=gnu99" CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS "${OBJECT_GEN_FLAGS} -std=c++11 " CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m3 -mthumb" CACHE INTERNAL "ASM Compiler options")
# set(CMAKE_LIB_ASM_FLAGS "${OBJECT_GEN_FLAGS} -x assembler-with-cpp " CACHE INTERNAL "ASM Compiler options")

# message(${CMAKE_SOURCE_DIR}/linker)
# -Wl,--gc-sections     Perform the dead code elimination.
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls, provide empty implementations for the POSIX system calls.
# set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections --specs=nano.specs --specs=nosys.specs -mthumb -mabi=aapcs -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")
set(CMAKE_EXE_LINKER_FLAGS "-L${CMAKE_SOURCE_DIR}/linker -x assembler-with-cpp -Tmain.ld -mcpu=cortex-m3 -mthumb -specs=nano.specs -Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections" CACHE INTERNAL "Linker options")
# set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m3 -T${LINKER_SCRIPT}" CACHE INTERNAL "Linker options")
# -T${CMAKE_SOURCE_DIR}/BSP/STM32F413ZHTx_FLASH.ld
#         -mcpu=cortex-m4
#         -mthumb
#         -mfpu=fpv4-sp-d16
#         -mfloat-abi=hard
#         -specs=nano.specs
#         -lc
#         -lm
#         -lnosys
#         -Wl,-Map=${PROJECT_NAME}.map,--cref
#         -Wl,--gc-sections
#---------------------------------------------------------------------------------------
# Set debug/release build configuration Options
#---------------------------------------------------------------------------------------

# Options for DEBUG build
# -Og   Enables optimizations that do not interfere with debugging.
# -g    Produce debugging information in the operating system’s native format.
set(CMAKE_C_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "C Compiler options for debug build type")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "C++ Compiler options for debug build type")
set(CMAKE_ASM_FLAGS_DEBUG "-g" CACHE INTERNAL "ASM Compiler options for debug build type")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE INTERNAL "Linker options for debug build type")

# Options for RELEASE build
# -Os   Optimize for size. -Os enables all -O2 optimizations.
# -flto Runs the standard link-time optimizer.
set(CMAKE_C_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "C Compiler options for release build type")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "C++ Compiler options for release build type")
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "ASM Compiler options for release build type")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto" CACHE INTERNAL "Linker options for release build type")


#---------------------------------------------------------------------------------------
# Set compilers
#---------------------------------------------------------------------------------------
set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-g++${TOOLCHAIN_EXT} CACHE INTERNAL "C++ Compiler")
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-as${TOOLCHAIN_EXT} CACHE INTERNAL "ASM Compiler")
# set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "ASM Compiler")
set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objcopy${TOOLCHAIN_EXT} CACHE INTERNAL "Obj copy")
set(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objdump${TOOLCHAIN_EXT} CACHE INTERNAL "Obj dump")
set(CMAKE_SIZE ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT} CACHE INTERNAL "Obj size")

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX}/${${TOOLCHAIN}} ${CMAKE_PREFIX_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

function(add_arm_executable EXECUTABLE_NAME)
    # set file names
    set(elf_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.elf)
    set(hex_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.hex)
    set(lss_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.lss)
    set(map_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.map)
    set(bin_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.bin)
    set(eep_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.eep)
    set(srec_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.srec)
    set(size_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.size)

    # set (${EXECUTABLE_NAME}_ELF_TARGET ${elf_file} PARENT_SCOPE)
    # set (${EXECUTABLE_NAME}_HEX_TARGET ${hex_file} PARENT_SCOPE)
    # set (${EXECUTABLE_NAME}_LSS_TARGET ${lss_file} PARENT_SCOPE)
    # set (${EXECUTABLE_NAME}_MAP_TARGET ${map_file} PARENT_SCOPE)
    # set (${EXECUTABLE_NAME}_BIN_TARGET ${bin_file} PARENT_SCOPE)
    # set (${EXECUTABLE_NAME}_EEP_TARGET ${eep_file} PARENT_SCOPE)
    # set (${EXECUTABLE_NAME}_SREC_TARGET ${srec_file} PARENT_SCOPE)
    # set (${EXECUTABLE_NAME}_SIZE_TARGET ${size_file} PARENT_SCOPE)

    # set(test_linker_flags "-T/linker/example.ld")
    # set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m3 -T${LINKER_SCRIPT}" CACHE INTERNAL "Linker options")

    # elf file
    add_executable(${elf_file} ${ARGN})
    
    # set(test_linker_flags "--linker_script=${LINKER_SCRIPT} -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs")
    # set(test_linker_flags "--specs=nosys.specs")
    # message(${CMAKE_OBJCOPY})
    # set_target_properties(
    #     ${elf_file}
    #     PROPERTIES
	#     # COMPILE_FLAGS "--specs=nosys.specs"
    #     COMPILE_FLAGS ${CMAKE_C_FLAGS}
    #     LINK_FLAGS ${CMAKE_EXE_LINKER_FLAGS}
    # )
    
    # add_custom_command(
    #     OUTPUT ${bin_file}
    #     COMMAND
    #     ${CMAKE_OBJCOPY} -O binary ${elf_file} ${bin_file}
    #     DEPENDS ${elf_file}
    # )

    # add_custom_command(
    #     OUTPUT ${hex_file}
    #     COMMAND
    #     ${CMAKE_OBJCOPY} -O ihex -R .eeprom -R .fuse -R .lock -R .signature ${elf_file} ${hex_file}
    #     COMMAND
    #     ${CMAKE_SIZE} ${elf_file}
    #     DEPENDS ${elf_file}
    # )

    # add_custom_command(
    #     OUTPUT ${eep_file}
    #     COMMAND
    #     ${CMAKE_OBJCOPY} -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary ${elf_file} ${eep_file} || exit 0
    #     DEPENDS ${elf_file}
    # )

    # add_custom_command(
    #     OUTPUT ${lss_file}
    #     COMMAND
    #     ${CMAKE_OBJDUMP} -h -S ${elf_file} > ${lss_file}
    #     DEPENDS ${elf_file}
    # )

    # add_custom_command(
    #     OUTPUT ${srec_file}
    #     COMMAND
    #     ${CMAKE_OBJCOPY} -O srec -R .eeprom -R .fuse -R .lock -R .signature  ${elf_file} ${srec_file}
    #     DEPENDS ${elf_file}
    # )
    
    # add_custom_command(
    #     OUTPUT ${size_file}
    #     COMMAND
    #     ${CMAKE_SIZE} ${elf_file}
    #     DEPENDS ${elf_file}
    # )

    # add_custom_target(
    #     ${EXECUTABLE_NAME}
    #     ALL
    #     DEPENDS ${hex_file} ${eep_file} ${lss_file} ${srec_file} ${size_file}
    # )

    add_custom_target(
        ${EXECUTABLE_NAME}
        ALL
        DEPENDS ${bin_file}
    )

    # set_target_properties(
    #     ${EXECUTABLE_NAME}
    #     PROPERTIES
    #     OUTPUT_NAME "${elf_file}"
    # )
endfunction(add_arm_executable)

function(add_arm_library LIBRARY_NAME)
    if(NOT ARGN)
        message(FATAL_ERROR "No source files given for ${LIBRARY_NAME}.")
    endif(NOT ARGN)

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

endfunction(add_arm_library)

function(arm_target_link_libraries EXECUTABLE_TARGET)
   if(NOT ARGN)
      message(FATAL_ERROR "Nothing to link to ${EXECUTABLE_TARGET}.")
   endif(NOT ARGN)

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
endfunction(arm_target_link_libraries EXECUTABLE_TARGET)
