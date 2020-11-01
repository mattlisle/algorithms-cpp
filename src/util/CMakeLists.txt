cmake_minimum_required(VERSION 3.2)
project(util)

set(SOURCE_FILES util.cpp)

add_library(util SHARED STATIC ${SOURCE_FILES})

install(TARGETS util DESTINATION ${LIB_DIR})
