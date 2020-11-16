cmake_minimum_required(VERSION 3.2)
project(sort)

set(SOURCE_FILES mergesort.cpp heapsort.cpp)

add_subdirectory(demo)

add_library(sort SHARED STATIC ${SOURCE_FILES})

install(TARGETS sort DESTINATION ${LIB_DIR})
