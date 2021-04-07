set(MODULE_TEST date_wrapper_tests)

add_executable(date_wrapper_tests ${SOURCE_FILES})

target_sources(date_wrapper_tests
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/test_date.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test_date_range.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test_datetime.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test_iso_date.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test_date_time_range.cpp"
)

target_link_libraries(date_wrapper_tests 
    PRIVATE
        project_options
        project_warnings
        date_wrapper
        gtest_main
)

gtest_discover_tests(date_wrapper_tests)
