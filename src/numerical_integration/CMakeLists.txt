set(TARGET numerical_integration)

add_library(${TARGET} numerical_integration.cpp)
target_include_directories(${TARGET} PUBLIC ${INCLUDES})
message(${INCLUDES})
