cmake_minimum_required(VERSION 3.6)

set(MODULE_TEST date_wrapper_tests)

project(${MODULE_TEST})

set(SOURCE_FILES
    test_datetime.cpp
    test_time_span.cpp
)

add_executable(${MODULE_TEST} ${SOURCE_FILES})

add_dependencies(${MODULE_TEST} gtest gtest_main gmock)

target_link_libraries(${MODULE_TEST} date_wrapper gtest gtest_main gmock)
