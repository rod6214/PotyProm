include_directories(${AVR-EXAMPLE_SOURCE_DIR}/lib)

add_subdirectory(lib)
# add_subdirectory(app)
# add_subdirectory(test)


if(__LOGIC_ANALYZER_TEST__)
    add_subdirectory(test)
else(__LOGIC_ANALYZER_TEST__)
    add_subdirectory(app)
endif(__LOGIC_ANALYZER_TEST__)
