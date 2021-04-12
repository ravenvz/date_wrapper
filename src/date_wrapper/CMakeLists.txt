# Download date lib at configure time
include(CMakeLists-datelib.txt)

add_library(date_wrapper INTERFACE)

# Add include directories as system to silence warnings from third party lib
target_include_directories(date_wrapper
    SYSTEM INTERFACE
        ${CMAKE_BINARY_DIR}/_deps/date_lib-src/include
)
target_include_directories(date_wrapper
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources(date_wrapper
    INTERFACE
        "${CMAKE_CURRENT_LIST_DIR}/include/date_wrapper/date_wrapper.h"
)

target_link_libraries(
    date_wrapper
    INTERFACE
        date_wrapper_options
        date_wrapper_warnings
)
