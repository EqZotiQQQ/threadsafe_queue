cmake_minimum_required(VERSION 3.16)

project(ThreadsafeQueue)

find_package(Threads REQUIRED)

set(HEADERS
        headers/ThreadsafeQueue.h
        )

set(SOURCES
        src/ThreadsafeQueue.cpp
        )

include_directories(
        headers
)

add_library(ThreadsafeQueue STATIC ${HEADERS} ${SOURCES})

target_link_libraries(ThreadsafeQueue PUBLIC Threads::Threads)

set(CMAKE_CXX_CPPCHECK "cppcheck")

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)

if (CMAKE_CXX_CPPCHECK)
    list(
            APPEND CMAKE_CXX_CPPCHECK
            "--enable=warning"
            "--inconclusive"
            "--force"
            "--inline-suppr"
    )
endif()