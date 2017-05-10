cmake_minimum_required(VERSION 3.8)

set(PROJECT date_wrapper_project)

project(${PROJECT})

set("${PROJECT}_BINARY_DIR" bin)
set("${PROJECT}_SOURCE_DIR" src)
set("${PROJECT}_LIB_DIR" lib)
set("${PROJECT}_ARCHIVE_DIR" lib/static)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_LIB_DIR})
set(ARCHIVE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_ARCHIVE_DIR})

set(EXECUTABLE_INSTALL_PATH_SUFFIX bin)
set(LIBRARY_INSTALL_PATH_SUFFIX lib)
set(THIRD_PARTY_LIBS_FOLDER third_party)

set(CMAKE_VERBOSE_MAKEFILE OFF)

option(BUILD_TESTS ON)

if (!WIN32)
    find_package(ECM REQUIRED NO_MODULE)
    set(CMAKE_MODULE_PATH ${ECM_MODULE_DIR})
    include(ECMEnableSanitizers)
endif()

set(EXECUTABLE_INSTALL_PATH_SUFFIX bin)
set(LIBRARY_INSTALL_PATH_SUFFIX lib)

add_subdirectory(src/date_wrapper)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
