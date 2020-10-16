cmake_minimum_required(VERSION 3.2)

project(sort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/division)

include_directories(${INCLUDE_DIR})
include_directories(${HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)


