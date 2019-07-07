cmake_minimum_required(VERSION 3.2)

project(${BUILD_FOLDER})

enable_testing()

message("BUILD_FOLDER = ${BUILD_FOLDER}")
add_subdirectory("${BUILD_FOLDER}")
