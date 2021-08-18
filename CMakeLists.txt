cmake_minimum_required(VERSION 3.16)

project(ThreadsafeQueue)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)   # include additional tools
include(utils)      # execute utils.3rdparty
include(cppcheck)      # execute utils.3rdparty
include(clang_formatter)      # execute utils.3rdparty

add_subdirectory(ThreadsafeQueue)

add_subdirectory(tests)
add_subdirectory(benchmark)
