add_library(UTIL OBJECT)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} UTIL_SRC)

target_sources(UTIL PRIVATE ${UTIL_SRC})

target_include_directories(UTIL PRIVATE ${INCLUDE_DIR})

list(APPEND LIBS UTIL)
set(LIBS ${LIBS} PARENT_SCOPE)
