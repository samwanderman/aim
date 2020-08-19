file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/aim/**/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/aim/**/*.h ${CMAKE_CURRENT_SOURCE_DIR}/aim/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/aim/*.h)

add_library(Aim STATIC ${Sources})

target_include_directories(Aim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
