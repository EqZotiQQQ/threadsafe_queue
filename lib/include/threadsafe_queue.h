#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>


template<class T>
class ThreadSafeQueue
{
private:
    std::queue<std::shared_ptr<T>> data;
    mutable std::mutex mtx;
    std::condition_variable not_empty;
    std::atomic<std::size_t> len {};
public:
    ThreadSafeQueue() = default;
    ThreadSafeQueue(ThreadSafeQueue&&) = delete;
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    void push(T new_value) {
        std::shared_ptr<T> sptr(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> l(mtx);
        data.push(sptr);
        len.fetch_add(1);
        not_empty.notify_one();
    }

    void wait_and_pop(T& value) {
        std::lock_guard<std::mutex> l(mtx);
        while (data.empty()) {
            not_empty.wait(l, [this]() { return !data.empty(); });
        }
        value = std::move(*data.front());
        data.pop();
        len.fetch_sub(1);
    }

    std::shared_ptr<T> wait_and_pop() {
        std::lock_guard<std::mutex> l(mtx);
        while (data.empty()) {
            not_empty.wait(l, [this]() { return !data.empty(); });
        }
        auto res(std::make_shared<T>(std::move(data.front())));
        data.pop();
        len.fetch_sub(1);
        return res;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> l(mtx);
        if (data.empty()) {
            return false;
        }
        value = std::move(*data.front());
        data.pop();
        len.fetch_sub(1);
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> l(mtx);
        if (data.empty()) {
            return std::make_shared<T>();
        }
        auto res = data.front();
        data.pop();
        len.fetch_sub(1);
        return res;
    }

    void clear() {
        while (!empty()) {
            try_pop();
        }
    }

    bool empty() const {
        return len.load() == 0;
    }

    std::size_t size() const {
        return len.load();
    }
};
