cmake_minimum_required(VERSION 3.16)

project(ThreadsafeQueue)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(ThreadsafeQueue)
add_subdirectory(tests)
add_subdirectory(benchmark)