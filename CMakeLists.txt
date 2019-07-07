cmake_minimum_required(VERSION 3.2)

project(${TARGET_FOLDER})

enable_testing()

message("TARGET_FOLDER = ${TARGET_FOLDER}")
add_subdirectory("${TARGET_FOLDER}")
