set(PROJECT_TESTS test_suite)
project(${PROJECT_TESTS})

find_package(Threads REQUIRED)

# Download GTest at configure time
include(CMakeLists-gtest.txt)

target_include_directories(gmock_main SYSTEM BEFORE INTERFACE
    "${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")

add_subdirectory(date_wrapper_tests)

