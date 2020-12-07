cmake_minimum_required(VERSION 3.2)
project(dp-test)

include_directories(${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp ${PROJECT_SOURCE_DIR}/src/dp-test.cpp)

add_executable(dp-test ${SOURCE_FILES})
target_link_libraries(dp-test dp gtest gmock)
install(TARGETS dp-test DESTINATION bin)
add_test(dp-tests dp-test)
