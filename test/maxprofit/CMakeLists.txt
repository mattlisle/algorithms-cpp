cmake_minimum_required(VERSION 3.2)
project(maxprofit-test)

include_directories(${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp ${PROJECT_SOURCE_DIR}/src/maxprofit-test.cpp)

add_executable(maxprofit-test ${SOURCE_FILES})
target_link_libraries(maxprofit-test maxprofit gtest)
install(TARGETS maxprofit-test DESTINATION bin)
add_test(maxprofit-tests maxprofit-test)
