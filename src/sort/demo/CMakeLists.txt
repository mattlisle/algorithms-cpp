cmake_minimum_required(VERSION 3.2)
project(sort-demo)

set(SOURCE_FILES main.cpp)

add_executable(sort-demo ${SOURCE_FILES})
target_link_libraries(sort-demo sort)
install(TARGETS sort-demo DESTINATION bin)
