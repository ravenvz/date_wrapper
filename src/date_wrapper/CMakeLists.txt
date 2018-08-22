set(MODULE date_wrapper)

project(${MODULE})

# Download date lib at configure time
include(CMakeLists-datelib.txt)

add_library(${MODULE} INTERFACE)

target_sources(${MODULE}
    INTERFACE
        "${CMAKE_CURRENT_LIST_DIR}/include/date_wrapper/DateTime.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/date_wrapper/IsoDate.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/date_wrapper/TimeSpan.h"
)

target_include_directories(${MODULE}
    INTERFACE include
    ${CMAKE_BINARY_DIR}/_deps/date_lib-src/include
)

target_compile_features(${MODULE} INTERFACE cxx_std_17)

if (WIN32)
    install(TARGETS ${MODULE} RUNTIME DESTINATION ${EXECUTABLE_INSTALL_PATH_SUFFIX})
else()
    install(TARGETS ${MODULE} LIBRARY DESTINATION ${LIBRARY_INSTALL_PATH_SUFFIX})
endif()
