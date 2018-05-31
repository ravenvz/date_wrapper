cmake_minimum_required(VERSION 3.11)

set(MODULE_TEST date_wrapper_tests)

project(${MODULE_TEST})

set(SOURCE_FILES
    test_datetime.cpp
    test_time_span.cpp
)

add_executable(${MODULE_TEST} ${SOURCE_FILES})

target_link_libraries(${MODULE_TEST} date_wrapper gtest_main)

gtest_add_tests(TARGET ${MODULE_TEST} TEST_PREFIX old:)
# gtest_discover_tests(${MODULE_TEST})