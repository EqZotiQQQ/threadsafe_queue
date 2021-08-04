#include "../headers/ThreadsafeQueue.h"

template<class T>
ThreadsafeQueue<T>::ThreadsafeQueue()
: size(0) {

}

template<class T>
void ThreadsafeQueue<T>::push(T new_value) {
    std::shared_ptr<T> sptr(std::make_shared<T>(std::move(new_value)));
    std::lock_guard<std::mutex> l(mtx);
    data.push(sptr);
    size.fetch_add(1);
    cv.notify_one();
}

template<class T>
void ThreadsafeQueue<T>::wait_and_pop(T& value) {
    std::lock_guard<std::mutex> l(mtx);
    cv.wait(l, [this]() {return !data.empty(); });
    value = std::move(*data.front());
    data.pop();
    size.fetch_sub(1);
}

template<class T>
std::shared_ptr<T> ThreadsafeQueue<T>::wait_and_pop() {
    std::lock_guard<std::mutex> l(mtx);
    cv.wait(l, [this]() {return !data.empty(); });
    auto res(std::make_shared<T>(std::move(data.front())));
    data.pop();
    size.fetch_sub(1);
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
    size.fetch_sub(1);
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
    size.fetch_sub(1);
    return res;
}

template<class T>
bool ThreadsafeQueue<T>::empty() const {
    std::lock_guard<std::mutex> l(mtx);
    return data.empty();
}

template<class T>
std::size_t ThreadsafeQueue<T>::len() const {
    std::lock_guard<std::mutex> l(mtx);
    return size;
}