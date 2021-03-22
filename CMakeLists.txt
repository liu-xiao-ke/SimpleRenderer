cmake_minimum_required(VERSION 3.17)
project(SimpleRenderer)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimpleRenderer src/main/main.cpp src/core/geometry.h src/core/geometry.cpp src/core/sr.h src/core/medium.cpp src/core/medium.h src/core/transform.cpp src/core/transform.h src/core/interaction.h src/core/interaction.cpp src/core/shape.h)