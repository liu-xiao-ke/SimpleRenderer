cmake_minimum_required(VERSION 3.17)
project(SimpleRenderer VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/core)
include_directories(src/shape)

add_subdirectory(src/core)
add_subdirectory(src/shape)
add_subdirectory(src/main)


