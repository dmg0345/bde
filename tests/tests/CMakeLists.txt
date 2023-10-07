# @brief Creates a test suite for 'cmocka' and adds it to 'ctest', each test suite maps to an executable target.
# @param[in] The name of the test suite to create.
function(define_test_suite TEST_SUITE_NAME)
    # Create executable for the test suite and link the test harness to it, along with the test utils.
    add_executable(${TEST_SUITE_NAME})
    target_link_libraries(${TEST_SUITE_NAME} PRIVATE cmocka)
    target_include_directories(${TEST_SUITE_NAME} PRIVATE
        "${PROJECT_ROOT_DIR}/tests/tests/.test_utils"
    )
    target_sources(${TEST_SUITE_NAME} PRIVATE
        "${PROJECT_ROOT_DIR}/tests/tests/.test_utils/cmocka_defs.c"
        "${PROJECT_ROOT_DIR}/tests/tests/.test_utils/samples/samples.c"
    )
    install(TARGETS ${TEST_SUITE_NAME} RUNTIME DESTINATION "${CMAKE_INSTALL_RUNTIMEDIR}")

    # Enable converage if enabled when deploying off-target, it is not possible to have coverage when on-target.
    if(${CFG_TESTS_ENABLE_COVERAGE} STREQUAL "ON")
        target_link_libraries(${TEST_SUITE_NAME} PRIVATE "gcov")
        target_compile_options(${TEST_SUITE_NAME} PRIVATE "-ftest-coverage" "-fprofile-arcs")
    endif()

    # If running on CI, then enable XML output on CMocka, otherwise use the default standard output.
    if((DEFINED CFG_CI) AND (${CFG_CI}))
        target_compile_definitions(${TEST_SUITE_NAME} PRIVATE "CMOCKA_JUNIT_XML_OUTPUT")
    endif()

    # Add test suite to CTest.
    add_test(NAME ${TEST_SUITE_NAME} COMMAND ${TEST_SUITE_NAME})
endfunction()

## Tests for Base64 and Base64URL ######################################################################################
add_subdirectory("base64")
