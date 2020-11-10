cmake_minimum_required(VERSION 3.2)
project(maxprofit)

set(SOURCE_FILES maxprofit.cpp)

add_subdirectory(demo)

add_library(maxprofit SHARED STATIC ${SOURCE_FILES})

install(TARGETS maxprofit DESTINATION ${LIB_DIR})
