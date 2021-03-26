cmake_minimum_required(VERSION 3.17)
project(SimpleRenderer VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(./src/core)
add_subdirectory(./src/shape)

add_executable(sr ${PROJECT_SOURCE_DIR}/src/main/main.cpp)

target_link_libraries(sr CORE SHAPE)