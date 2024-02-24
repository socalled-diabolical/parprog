set(TARGET pi_calc)

add_executable(${TARGET} pi_calc.cpp)

target_link_libraries(${TARGET} numerical_integration)
