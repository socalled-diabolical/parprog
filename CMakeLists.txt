set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/headers)

cmake_minimum_required(VERSION 3.20)
project(pi_calc)

set(CXX_STANDARD C++17)

# Directories with libraries 
add_subdirectory(src)

# Directories with executables
add_subdirectory(pi_calculation)
