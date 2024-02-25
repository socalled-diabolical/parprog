set(TARGET pi_calc)

add_executable(${TARGET} pi_calc.cpp)

message("trying to include " ${INCLUDES})

target_include_directories(${TARGET} PRIVATE ${INCLUDES})
target_link_libraries(${TARGET} numerical_integration ${MPI_C_LIBRARIES})
