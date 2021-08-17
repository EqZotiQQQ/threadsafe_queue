#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>


/*
 * use sptr is overhead for primitive types
 * but for classes created by user its much better because no need to copy whole object from list.
 * With sptr we avoid problems like mem leaks
 * */
template<class T>
class ThreadsafeQueue {
private:
    std::queue<std::shared_ptr<T>> data;
    mutable std::mutex mtx;
    std::condition_variable not_empty;
    std::atomic<std::size_t> len {};  // can keep int, cuz of all actions under guards
public:
    ThreadsafeQueue();
    ThreadsafeQueue(const std::size_t size);  //fill n element with zeros
    ThreadsafeQueue(const std::initializer_list<T>& initial_list); // list{elem1, elem2, ...}


    void push(T new_value);

    void wait_and_pop(T& value);
    std::shared_ptr<T> wait_and_pop();
    bool try_pop(T& value);
    std::shared_ptr<T> try_pop();

    void clear();

    bool empty() const;
    std::size_t size() const;
};