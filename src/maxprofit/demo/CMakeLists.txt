cmake_minimum_required(VERSION 3.2)
project(maxprofit-demo)

set(SOURCE_FILES main.cpp)

add_executable(maxprofit-demo ${SOURCE_FILES})

target_link_libraries(maxprofit-demo maxprofit util)

install(TARGETS maxprofit-demo DESTINATION bin)
