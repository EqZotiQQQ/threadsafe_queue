#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

template<class T>
class ThreadsafeQueue {
private:
    std::queue<std::shared_ptr<T>> data;
    mutable std::mutex mtx;
    std::condition_variable cv;
    std::atomic<int> size;  // can keep int, cuz of all actions under guards
public:
    ThreadsafeQueue();

    void push(T new_value);

    void wait_and_pop(T& value);
    std::shared_ptr<T> wait_and_pop();
    bool try_pop(T& value);
    std::shared_ptr<T> try_pop();

    bool empty() const;
    std::size_t len() const;
};