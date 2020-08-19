add_executable(SerialTest SerialTest.cpp)
add_executable(ConcurrentQueueTest ConcurrentQueueTest.cpp)

target_link_libraries(SerialTest Aim)
target_link_libraries(ConcurrentQueueTest Aim)

target_include_directories(SerialTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_include_directories(ConcurrentQueueTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
