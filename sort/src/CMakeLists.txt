cmake_minimum_required(VERSION 3.2)
project(sort)

add_executable(sort ${SOURCE_FILES})
install(TARGETS sort DESTINATION ${BIN_DIR})
