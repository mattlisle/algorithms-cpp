cmake_minimum_required(VERSION 3.2)
project(sort_test)

include_directories(${HEADERS_DIR})

set(SOURCE_FILES main.cpp src/sort_test.cpp)

add_executable(sort_test ${SOURCE_FILES})
target_link_libraries(sort_test sort gtest)
install(TARGETS sort_test DESTINATION bin)

