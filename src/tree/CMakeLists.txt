cmake_minimum_required(VERSION 3.2)
project(tree)

set(SOURCE_FILES binarytree.cpp)

add_subdirectory(demo)

add_library(tree SHARED STATIC ${SOURCE_FILES})
target_link_libraries(tree util)
install(TARGETS tree DESTINATION ${LIB_DIR})
