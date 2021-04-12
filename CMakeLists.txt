cmake_minimum_required(VERSION 3.15)

set(PROJECT date_wrapper_project VERSION 0.8.4)

project(${PROJECT})

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

set(CMAKE_VERBOSE_MAKEFILE OFF)

option(BUILD_TESTS OFF)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(date_wrapper_options INTERFACE)
target_compile_features(date_wrapper_options INTERFACE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        target_compile_options(date_wrapper_options INTERFACE -ftime-trace)
    endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(date_wrapper_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(date_wrapper_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(date_wrapper_options)

# enable doxygen
# include(cmake/Doxygen.cmake)
# enable_doxygen()

add_subdirectory(src/date_wrapper)

if (BUILD_TESTS)
	enable_testing()
	include(GoogleTest)
    add_subdirectory(tests)
endif()
