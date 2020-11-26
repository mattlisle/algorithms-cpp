cmake_minimum_required(VERSION 3.2)
project(tree-test)

include_directories(${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp ${PROJECT_SOURCE_DIR}/src/tree-test.cpp)

add_executable(tree-test ${SOURCE_FILES})
target_link_libraries(tree-test tree gtest)
install(TARGETS tree-test DESTINATION bin)
add_test(tree-tests tree-test)
