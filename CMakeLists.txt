set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CPP_COMPILER mpic++)

message("using c++ compiler = " ${CMAKE_CPP_COMPILER})

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/headers)
cmake_minimum_required(VERSION 3.20)
project(pi_calc)

set(CXX_STANDARD C++20)


find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
# Directories with libraries 
add_subdirectory(src)

# Directories with executables
add_subdirectory(pi_calculation)
