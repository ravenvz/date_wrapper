cmake_minimum_required(VERSION 3.11)

set(MODULE_TEST date_wrapper_tests)

project(${MODULE_TEST})

add_executable(${MODULE_TEST} ${SOURCE_FILES})

target_sources(${MODULE_TEST}
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/test_date.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test_date_span.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test_datetime.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test_iso_date.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test_time_span.cpp"
)

target_link_libraries(${MODULE_TEST} date_wrapper gtest_main)

gtest_discover_tests(${MODULE_TEST})
