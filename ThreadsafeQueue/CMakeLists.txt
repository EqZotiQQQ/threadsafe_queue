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
