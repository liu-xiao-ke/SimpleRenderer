aux_source_directory(. SR_SHAPE_SOURCES)

add_library(SHAPES ${SR_SHAPE_SOURCES})
target_include_directories(SHAPES PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})