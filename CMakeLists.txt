cmake_minimum_required(VERSION 3.11)

set(PROJECT date_wrapper_project VERSION 0.8.0)

project(${PROJECT})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/static)

set(CMAKE_VERBOSE_MAKEFILE OFF)

option(BUILD_TESTS OFF)

if (!WIN32)
    find_package(ECM REQUIRED NO_MODULE)
    set(CMAKE_MODULE_PATH ${ECM_MODULE_DIR})
    include(ECMEnableSanitizers)
endif()

add_subdirectory(src/date_wrapper)

if (BUILD_TESTS)
	enable_testing()
	include(GoogleTest)
    add_subdirectory(tests)
endif()
