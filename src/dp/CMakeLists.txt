cmake_minimum_required(VERSION 3.2)
project(dp)

set(SOURCE_FILES cutrod.cpp matrixorder.cpp)

add_library(dp SHARED STATIC ${SOURCE_FILES})
target_link_libraries(dp util)
install(TARGETS dp DESTINATION ${LIB_DIR})
