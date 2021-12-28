project(threadsafe_queue_benchmarks)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(../lib/include)

target_link_libraries(${PROJECT_NAME} threadsafe_queue_impl)
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)
