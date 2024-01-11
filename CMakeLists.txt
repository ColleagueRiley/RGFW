cmake_minimum_required(VERSION 3.27)
project(RGFW)

set(CMAKE_CXX_STANDARD 11)

add_library(RGFW INTERFACE)
target_include_directories(RGFW INTERFACE .)

add_subdirectory(samples/gl33)
