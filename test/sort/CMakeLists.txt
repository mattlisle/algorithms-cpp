cmake_minimum_required(VERSION 3.2)
project(sort-test)

include_directories(${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp ${PROJECT_SOURCE_DIR}/src/sort-test.cpp)

add_executable(sort-test ${SOURCE_FILES})
target_link_libraries(sort-test sort gtest)
install(TARGETS sort-test DESTINATION bin)

