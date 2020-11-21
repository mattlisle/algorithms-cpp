cmake_minimum_required(VERSION 3.2)
project(linkedlist-test)

include_directories(${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp ${PROJECT_SOURCE_DIR}/src/linkedlist-test.cpp)

add_executable(linkedlist-test ${SOURCE_FILES})
target_link_libraries(linkedlist-test gtest)
install(TARGETS linkedlist-test DESTINATION bin)
add_test(linkedlist-tests linkedlist-test)
