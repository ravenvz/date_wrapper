cmake_minimum_required(VERSION 3.6)

set(MODULE date_wrapper)

project(${MODULE})

set(SOURCE_FILES
    src/DateTime.cpp
    src/TimeSpan.cpp
)

set(HEADER_FILES_FOR_CLION
    include/date_wrapper/DateTime.h
    include/date_wrapper/TimeSpan.h
)

include(ExternalProject)
include(CMakeLists-datelib.txt)

add_library(${MODULE} SHARED ${SOURCE_FILES} ${HEADER_FILES_FOR_CLION})

add_dependencies(${MODULE} DateLib)

target_compile_features(${MODULE} PUBLIC cxx_return_type_deduction)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    target_compile_options(${MODULE} PUBLIC ${CLANG_COMPILE_OPTIONS})
elseif(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${MODULE} PUBLIC ${GCC_COMPILE_OPTIONS})
else()
    message(${CMAKE_COMPILER_ID} "compiler might not be supported yet.")
endif()

target_include_directories(${MODULE}
    PUBLIC include
    PUBLIC ${DateLib_INCLUDE_DIRS}
)

target_link_libraries(${MODULE} INTERFACE DateLib)

target_compile_features(${MODULE} PUBLIC cxx_return_type_deduction)

install(TARGETS ${MODULE} LIBRARY DESTINATION ${EXECUTABLE_INSTALL_PATH_SUFFIX})

