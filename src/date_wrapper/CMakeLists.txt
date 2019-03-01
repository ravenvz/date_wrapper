set(MODULE date_wrapper)

project(${MODULE})

# Download date lib at configure time
include(CMakeLists-datelib.txt)

add_library(${MODULE} INTERFACE)

target_sources(${MODULE}
    INTERFACE
        "${CMAKE_CURRENT_LIST_DIR}/include/date_wrapper/date_wrapper.h"
)

target_include_directories(${MODULE}
    INTERFACE include
    ${CMAKE_BINARY_DIR}/_deps/date_lib-src/include
)

target_compile_features(${MODULE} INTERFACE cxx_std_17)
