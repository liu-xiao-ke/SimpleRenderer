cmake_minimum_required(VERSION 3.17)
project(SimpleRenderer)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimpleRenderer src/main/main.cpp src/core/geometry.h src/core/geometry.cpp src/core/sr.h)