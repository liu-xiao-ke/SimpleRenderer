aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/. SR_CORE_SOURCES)

add_library(LIB_CORE SHARED ${SR_CORE_SOURCES})

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(LIB_CORE PUBLIC ${INCLUDE_DIRS})