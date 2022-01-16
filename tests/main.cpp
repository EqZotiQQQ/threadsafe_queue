#include "threadsafe_queue.h"
#include "gtest/gtest.h"

#include <thread>

/*
 * It's simple but i dont want to do that right now
 * */

struct A{
    int x;
};

TEST(TestThreadsafeQueueA, CreateQueue)
{
    ThreadSafeQueue<A> queue;
    queue.push(A{.x=42});
    queue.push(A{.x=142});
    queue.push(A{.x=1142});
    queue.push(A{.x=11142});

    ASSERT_EQ(queue.try_pop()->x, 42);
    ASSERT_EQ(queue.size(), 3);
}


TEST(TestThreadsafeQueue, CreateQueue)
{
    ThreadSafeQueue<int> queue;
    ASSERT_EQ(queue.size(), 0);
}

TEST(TestThreadsafeQueue, TryPopEmptyQueue)
{
    ThreadSafeQueue<int> queue{};
    int x;
    ASSERT_FALSE(queue.try_pop(x));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
