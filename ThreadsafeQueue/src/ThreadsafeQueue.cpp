#include "ThreadsafeQueue.h"

template<class T>
ThreadsafeQueue<T>::ThreadsafeQueue() {}

template<class T>
ThreadsafeQueue<T>::ThreadsafeQueue(const std::size_t size) {
    for (int i = 0; i < size; i++) {
        push(0);
    }
}

template<class T>
ThreadsafeQueue<T>::ThreadsafeQueue(const std::initializer_list<T>& initial_list) {
    for (const auto& item: initial_list) {
        push(item);
    }
}

template<class T>
void ThreadsafeQueue<T>::push(T new_value) {
    std::shared_ptr<T> sptr(std::make_shared<T>(std::move(new_value)));
    std::lock_guard<std::mutex> l(mtx);
    data.push(sptr);
    len.fetch_add(1);
    not_empty.notify_one();
}

template<class T>
void ThreadsafeQueue<T>::wait_and_pop(T& value) {
    std::lock_guard<std::mutex> l(mtx);
    while (data.empty()) {
        not_empty.wait(l, [this]() { return !data.empty(); });
    }
    value = std::move(*data.front());
    data.pop();
    len.fetch_sub(1);
}

template<class T>
std::shared_ptr<T> ThreadsafeQueue<T>::wait_and_pop() {
    std::lock_guard<std::mutex> l(mtx);
    while (data.empty()) {
        not_empty.wait(l, [this]() { return !data.empty(); });
    }
    auto res(std::make_shared<T>(std::move(data.front())));
    data.pop();
    len.fetch_sub(1);
    return res;
}

template<class T>
bool ThreadsafeQueue<T>::try_pop(T& value) {
    std::lock_guard<std::mutex> l(mtx);
    if (data.empty()) {
        return false;
    }
    value = std::move(*data.front());
    data.pop();
    len.fetch_sub(1);
    return true;
}

template<class T>
std::shared_ptr<T> ThreadsafeQueue<T>::try_pop() {
    std::lock_guard<std::mutex> l(mtx);
    if (data.empty()) {
        return std::make_shared<T>();
    }
    auto res = data.front();
    data.pop();
    len.fetch_sub(1);
    return res;
}

template<class T>
bool ThreadsafeQueue<T>::empty() const {
    std::lock_guard<std::mutex> l(mtx);
    return data.empty();
}

template<class T>
std::size_t ThreadsafeQueue<T>::size() const {
    std::lock_guard<std::mutex> l(mtx);
    return len;
}

template<class T>
void ThreadsafeQueue<T>::clear() {
    while(!empty()) {
        try_pop();
    }
}
