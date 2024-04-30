set(TARGET time_communicators)

add_executable(${TARGET} time_communicators.cpp)

target_include_directories(${TARGET} PRIVATE ${INCLUDES})
target_link_libraries(${TARGET} ${MPI_C_LIBRARIES})
