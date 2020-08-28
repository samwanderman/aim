file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/aim/**/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/aim/**/*.h ${CMAKE_CURRENT_SOURCE_DIR}/aim/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/aim/*.h)

add_library(Aim STATIC ${Sources})

find_package(Threads REQUIRED)
target_link_libraries(Aim PRIVATE Threads::Threads)

target_include_directories(Aim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
