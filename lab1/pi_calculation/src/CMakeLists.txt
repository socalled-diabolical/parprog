set(TARGET pi_calc)

add_executable(${TARGET} pi_calc.cpp)

target_include_directories(${TARGET} PRIVATE ${INCLUDES})
target_link_libraries(${TARGET} numerical_integration ${MPI_C_LIBRARIES})
