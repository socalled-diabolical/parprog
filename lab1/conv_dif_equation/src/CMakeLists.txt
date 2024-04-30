set(TARGET conv_dif_equation)

add_executable(${TARGET} conv_dif_equation.cpp)

target_include_directories(${TARGET} PRIVATE ${INCLUDES})
target_link_libraries(${TARGET} ${MPI_C_LIBRARIES})
