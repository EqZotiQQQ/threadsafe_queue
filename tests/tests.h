#ifndef THREADSAFEQUEUE_TESTS_H
#define THREADSAFEQUEUE_TESTS_H

#include "gtest/gtest.h"
#include "../ThreadsafeQueue/headers/ThreadsafeQueue.h"
#include "../ThreadsafeQueue/src/ThreadsafeQueue.cpp"
#include <iostream>

class TestThreadsafeQueue: public ::testing::Test {
protected:
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    void SetUp()
    {
        std::cout << "setup" << std::endl;
    }
    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    void TearDown()
    {
        std::cout << "teardown" << std::endl;
    }
};

#endif //THREADSAFEQUEUE_TESTS_H
