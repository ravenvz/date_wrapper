cmake_minimum_required(VERSION 3.8)

set(PROJECT_TESTS test_suite)
project(${PROJECT_TESTS})

find_package(Threads REQUIRED)

include(ExternalProject)
include(CMakeLists-gtest.txt)

add_subdirectory(date_wrapper_tests)

