aux_source_directory(src/. SR_CORE_SOURCES)

add_library(LIB_CORE ${SR_CORE_SOURCES})
target_include_directories(LIB_CORE PUBLIC include)