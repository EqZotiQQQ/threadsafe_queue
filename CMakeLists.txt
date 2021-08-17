cmake_minimum_required(VERSION 3.16)

project(ThreadsafeQueue)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)   # include additional tools
include(utils)      # execute utils.cmake

add_subdirectory(ThreadsafeQueue)

add_subdirectory(tests)
add_subdirectory(benchmark)
