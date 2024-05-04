add_library(UTILS OBJECT)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} UTILS_SRC)

target_sources(UTILS PRIVATE ${UTILS_SRC})

target_include_directories(UTILS PRIVATE ${INCLUDE_DIR})

list(APPEND LIBS UTILS)
set(LIBS ${LIBS} PARENT_SCOPE)
