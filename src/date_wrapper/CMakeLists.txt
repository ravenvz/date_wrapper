set(MODULE date_wrapper)

project(${MODULE})

set(HEADER_FILES_FOR_CLION
    include/date_wrapper/DateTime.h
    include/date_wrapper/TimeSpan.h
)

set(THIRD_PARTY_LIBS_FOLDER third_party)

add_library(${MODULE} INTERFACE)

add_dependencies(${MODULE} DateLib)

# if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
#     target_compile_options(${MODULE} PUBLIC ${CLANG_COMPILE_OPTIONS})
# elseif(CMAKE_COMPILER_IS_GNUCXX)
#     target_compile_options(${MODULE} PUBLIC ${GCC_COMPILE_OPTIONS})
# else()
#     message(${CMAKE_COMPILER_ID} "compiler might not be supported yet.")
# endif()

# Download date lib at configure time
message("Downloading date")
configure_file(CMakeLists-datelib.txt date-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/date-download )
if(result)
  message(FATAL_ERROR "CMake download step for date failed: ${result}")
endif()
message("Downloaded date")
# message("Building date")
# execute_process(COMMAND ${CMAKE_COMMAND} --build .
  # RESULT_VARIABLE result
  # WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/date-download )
# if(result)
  # message(FATAL_ERROR "Build step for date failed: ${result}")
# endif()
# message("date built successfully")

target_include_directories(${MODULE}
    INTERFACE include
	${CMAKE_CURRENT_SOURCE_DIR}/${THIRD_PARTY_LIBS_FOLDER}/date/include
)

target_compile_features(${MODULE} INTERFACE cxx_std_17)

if (WIN32)
    install(TARGETS ${MODULE} RUNTIME DESTINATION ${EXECUTABLE_INSTALL_PATH_SUFFIX})
else()
    install(TARGETS ${MODULE} LIBRARY DESTINATION ${LIBRARY_INSTALL_PATH_SUFFIX})
endif()
