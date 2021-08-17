#include "gtest/gtest.h"

#include "../ThreadsafeQueue/headers/ThreadsafeQueue.h"
#include "../ThreadsafeQueue/src/ThreadsafeQueue.cpp"

#include <thread>

TEST(TestThreadsafeQueue, CreateQueue) {
    ThreadsafeQueue<int> queue;
    ASSERT_EQ(queue.size(),0);
}

TEST(TestThreadsafeQueue, CreateQueueZeros) {
    ThreadsafeQueue<int> queue(10);
    ASSERT_EQ(queue.size(), 10);
}

TEST(TestThreadsafeQueue, CreateQueueInitList) {
    ThreadsafeQueue<int> queue{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    ASSERT_EQ(queue.size(), 20);
}

TEST(TestThreadsafeQueue, TryPopEmptyQueue) {
    ThreadsafeQueue<int> queue{};
    int x;
    ASSERT_FALSE(queue.try_pop(x));
}

TEST(TestThreadsafeQueue, TryPop) {
    ThreadsafeQueue<int> queue{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    auto f = [&] {
        for (int i = 0; i < 11; i++) {
            int x;
            queue.try_pop(x);
        }
    };
    std::thread worker1(f);
    std::thread worker2(f);
    worker1.join();
    worker2.join();
    ASSERT_EQ(queue.size(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
