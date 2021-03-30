aux_source_directory(. SR_CORE_SOURCES)

add_library(CORE ${SR_CORE_SOURCES})
target_include_directories(CORE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})