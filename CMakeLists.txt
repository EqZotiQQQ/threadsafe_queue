cmake_minimum_required(VERSION 3.16)

project(lib)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)   # include additional tools
#include(utils)
include(cppcheck)
include(clang_formatter)

include_directories(tests)
include_directories(benchmark)

add_subdirectory(lib)

add_subdirectory(tests)
add_subdirectory(benchmark)

add_subdirectory(third_party/googletest)
add_subdirectory(third_party/benchmark)

add_compile_options(-Wall -Wextra -pedantic -Werror)
