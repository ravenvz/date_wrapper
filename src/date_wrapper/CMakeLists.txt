set(MODULE date_wrapper)

project(${MODULE})

set(HEADER_FILES_FOR_CLION
    include/date_wrapper/DateTime.h
    include/date_wrapper/TimeSpan.h
)

# Download date lib at configure time
include(CMakeLists-datelib.txt)

add_library(${MODULE} INTERFACE)

# if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
#     target_compile_options(${MODULE} PUBLIC ${CLANG_COMPILE_OPTIONS})
# elseif(CMAKE_COMPILER_IS_GNUCXX)
#     target_compile_options(${MODULE} PUBLIC ${GCC_COMPILE_OPTIONS})
# else()
#     message(${CMAKE_COMPILER_ID} "compiler might not be supported yet.")
# endif()

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
