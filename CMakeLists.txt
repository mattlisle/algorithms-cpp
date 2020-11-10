cmake_minimum_required(VERSION 3.2)

project(algorithms-cpp)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${INCLUDE_DIR}/algorithms-cpp)

add_subdirectory(src/util)
add_subdirectory(src/sort)
add_subdirectory(test/sort)
add_subdirectory(src/maxprofit)
add_subdirectory(lib/googletest)
