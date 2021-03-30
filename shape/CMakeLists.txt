aux_source_directory(src/. SR_SHAPE_SOURCES)

add_library(LIB_SHAPES ${SR_SHAPE_SOURCES})
target_include_directories(LIB_SHAPES PUBLIC include ../core/include)