cmake_minimum_required(VERSION 3.2)
project(linkedlist-demo)

set(SOURCE_FILES main.cpp)

add_executable(linkedlist-demo ${SOURCE_FILES})
target_link_libraries(linkedlist-demo util)
install(TARGETS linkedlist-demo DESTINATION bin)
