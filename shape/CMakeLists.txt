aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/. SR_SHAPE_SOURCES)

add_library(LIB_SHAPES SHARED ${SR_SHAPE_SOURCES})

set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../core/include)

target_include_directories(LIB_SHAPES PUBLIC ${INCLUDE_DIRS})