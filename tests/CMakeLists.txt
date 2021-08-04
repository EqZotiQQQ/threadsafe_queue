project(ThreadsafeQueue_tests)

add_subdirectory(googletest)

add_executable(ThreadsafeQueue_tests main.cpp tests.cpp tests.h)

target_link_libraries(ThreadsafeQueue_tests ThreadsafeQueue)
target_link_libraries(ThreadsafeQueue_tests gtest gtest_main)