cmake_minimum_required(VERSION 3.16)

project(threadsafe_queue_impl)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

set(HEADERS
        include/threadsafe_queue.h
        )

set(SOURCES
        src/threadsafe_queue.cpp
        )

include_directories(
        include
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
