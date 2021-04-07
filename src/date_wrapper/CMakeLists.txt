# Download date lib at configure time
include(CMakeLists-datelib.txt)

add_library(date_wrapper INTERFACE)

target_sources(date_wrapper
    INTERFACE
        "${CMAKE_CURRENT_LIST_DIR}/include/date_wrapper/date_wrapper.h"
)

target_include_directories(date_wrapper
    INTERFACE include
    ${CMAKE_BINARY_DIR}/_deps/date_lib-src/include
)

target_compile_features(date_wrapper INTERFACE cxx_std_17)
