include_directories(${AVR-EXAMPLE_SOURCE_DIR}/lib)

add_subdirectory(lib)

if(NOT LOGIC_ANALYZER_TEST)
    add_subdirectory(app)
else(NOT LOGIC_ANALYZER_TEST)
    add_compile_definitions(__LOGIC_ANALYZER_TEST__)
    add_subdirectory(test)
endif(NOT LOGIC_ANALYZER_TEST)
