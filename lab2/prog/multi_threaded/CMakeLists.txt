set(TARGET multi_threaded)
add_executable(${TARGET} multi_threaded.cpp)

target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/headers)
target_compile_options(${TARGET} PUBLIC "-std=c++20")
