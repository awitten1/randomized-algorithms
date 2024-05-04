cmake_minimum_required(VERSION 3.24)

project(randomized-algorithms CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

include(cmake/deps.cmake)

add_subdirectory(utils)
add_subdirectory(chapter1)
