add_library(SR_CORE SHARED
        core/geometry.cpp
        core/interaction.cpp
        core/shape.cpp
        core/medium.cpp
        core/transform.cpp
        shape/sphere.cpp
        core/spectrum.cpp)

add_subdirectory(main)

target_include_directories(SR_CORE PUBLIC ${PROJECT_SOURCE_DIR}/include)

