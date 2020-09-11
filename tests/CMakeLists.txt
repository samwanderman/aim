add_executable(ConcurrentQueueTest ConcurrentQueueTest.cpp)
add_executable(NonBlockingQueueTest NonBlockingQueueTest.cpp)
add_executable(SerialTest SerialTest.cpp)
add_executable(LogTest LogTest.cpp)

target_link_libraries(ConcurrentQueueTest Aim)
target_link_libraries(NonBlockingQueueTest Aim)
target_link_libraries(SerialTest Aim)
target_link_libraries(LogTest Aim)

target_include_directories(ConcurrentQueueTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_include_directories(NonBlockingQueueTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_include_directories(SerialTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_include_directories(LogTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
