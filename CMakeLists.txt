cmake_minimum_required(VERSION 3.17)
project(SimpleRenderer VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

set(SR_MAIN ${PROJECT_SOURCE_DIR}/src/main/main.cpp)

set(SR_CORE_SOURCES
        ${PROJECT_SOURCE_DIR}/src/core/geometry.cpp
        ${PROJECT_SOURCE_DIR}/src/core/interaction.cpp
        ${PROJECT_SOURCE_DIR}/src/core/shape.cpp
        ${PROJECT_SOURCE_DIR}/src/core/medium.cpp
        ${PROJECT_SOURCE_DIR}/src/core/transform.cpp)

set(SR_CORE_HEADERS
        ${PROJECT_SOURCE_DIR}/src/core/sr.h
        ${PROJECT_SOURCE_DIR}/src/core/transform.h
        ${PROJECT_SOURCE_DIR}/src/core/geometry.h
        ${PROJECT_SOURCE_DIR}/src/core/interaction.h
        ${PROJECT_SOURCE_DIR}/src/core/medium.h
        ${PROJECT_SOURCE_DIR}/src/core/shape.h)

set(SR_SHAPE_SOURCES
        ${PROJECT_SOURCE_DIR}/src/shape/sphere.cpp)

set(SR_SHAPE_HEADERS
        ${PROJECT_SOURCE_DIR}/src/shape/sphere.h)

add_executable(sr_exe ${SR_MAIN} ${SR_CORE_SOURCES} ${SR_SHAPE_SOURCES})

target_include_directories(sr_exe PUBLIC SR_CORE_HEADERS SR_SHAPE_HEADERS)