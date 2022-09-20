cmake_minimum_required(VERSION 3.14)

enable_language(C ASM)

project(testApp)


# add_executable(testApp src/main.c)
add_executable(testLib src/test.s)

# set_target_properties(
#         ${testLib}
#         PROPERTIES
# 	    COMPILE_FLAGS "-mcpu=cortex-m3 -mthumb"
#         # COMPILE_FLAGS ${CMAKE_C_FLAGS}
#         # LINK_FLAGS ${CMAKE_EXE_LINKER_FLAGS}
#     )

add_custom_command(
        OUTPUT test.o
        COMMAND
        ${CMAKE_ASM_COMPILER} "-mcpu=cortex-m3 -mthumb"
    )

# add_library(testAppLib OBJECT src/test.s)
# add_executable(testApp src/main.c)
# add_library(testLib OBJECT src/test.s)
# link_directories(".")
# target_compile_options(testApp PRIVATE ${CMAKE_C_FLAGS})
# target_compile_options(testLib PRIVATE ${CMAKE_ASM_FLAGS})
# target_compile_options(testAppLib PRIVATE ${CMAKE_ASM_FLAGS})

# target_link_options(testApp PRIVATE ${CMAKE_EXE_LINKER_FLAGS})
# target_link_libraries(testApp testLib)
# target_link_libraries(myexe mylib)
# add_custom_command(TARGET testApp
#         POST_BUILD
#         COMMAND arm-none-eabi-objcopy -O ihex testApp ${PROJECT_NAME}.hex
#         COMMAND arm-none-eabi-objcopy -O binary testApp ${PROJECT_NAME}.bin)