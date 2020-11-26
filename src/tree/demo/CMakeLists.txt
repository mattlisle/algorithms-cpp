cmake_minimum_required(VERSION 3.2)
project(tree-demo)

set(SOURCE_FILES main.cpp)

add_executable(tree-demo ${SOURCE_FILES})

target_link_libraries(tree-demo tree util)

install(TARGETS tree-demo DESTINATION bin)
