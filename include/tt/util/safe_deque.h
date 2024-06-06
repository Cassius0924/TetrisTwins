#ifndef UTIL_SAFE_DEQUE_H
#define UTIL_SAFE_DEQUE_H

#include <mutex>
#include <condition_variable>
#include <deque>

namespace util::stl {

template <typename T>
class SafeDeque {
private:
    std::deque<T> _deque;
    std::mutex _mutex;
    std::condition_variable _cv;

    using iterator = typename std::deque<T>::iterator;

public:
    SafeDeque() = default;

    ~SafeDeque() = default;

    // 拷贝构造函数
    SafeDeque(const SafeDeque &other) {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque = other;
    }

    // 拷贝赋值运算符
    SafeDeque &operator=(const SafeDeque &other) {
        if (this != &other) {
            std::lock_guard<std::mutex> lock1(_mutex);
            std::lock_guard<std::mutex> lock2(other._mutex);
            _deque = other._deque;
        }
        return *this;
    }

    // 移动构造函数
    SafeDeque(const SafeDeque &&other) noexcept {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque = std::move(other);
    }

    // 移动赋值运算符
    SafeDeque &operator=(const SafeDeque &&other) noexcept {
        if (this != &other) {
            std::lock_guard<std::mutex> lock1(_mutex);
            std::lock_guard<std::mutex> lock2(other._mutex);
            _deque = std::move(other._deque);
        }
        return *this;
    }

    void push_back(const T &value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque.push_back(value);
        _cv.notify_one();
    }

    void push_back(T &&value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque.push_back(std::move(value));
        _cv.notify_one();
    }

    void push_front(const T &value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque.push_front(value);
        _cv.notify_one();
    }

    void push_front(T &&value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque.push_front(std::move(value));
        _cv.notify_one();
    }

    template <typename... Args>
    void emplace_back(Args &&...args) {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque.emplace_back(std::forward<Args>(args)...);
        _cv.notify_one();
    }

    template <typename... Args>
    void emplace_front(Args &&...args) {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque.emplace_front(std::forward<Args>(args)...);
        _cv.notify_one();
    }

    void pop_back() {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_deque.empty()) {
            _cv.wait(lock);
        }
        _deque.pop_back();
    }

    void pop_front() {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_deque.empty()) {
            _cv.wait(lock);
        }
        _deque.pop_front();
    }

    T front() {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_deque.empty()) {
            _cv.wait(lock);
        }
        return _deque.front();
    }

    T back() {
        std::unique_lock<std::mutex> lock(_mutex);
        while (_deque.empty()) {
            _cv.wait(lock);
        }
        return _deque.back();
    }

    int size() {
        std::lock_guard<std::mutex> lock(_mutex);
        return _deque.size();
    }

    int empty() {
        std::lock_guard<std::mutex> lock(_mutex);
        return _deque.empty();
    }

    void clear() {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque.clear();
    }

    void resize(int size) {
        std::lock_guard<std::mutex> lock(_mutex);
        _deque.resize(size);
    }

    T &operator[](int index) {
        std::lock_guard<std::mutex> lock(_mutex);
        return _deque[index];
    }

    iterator begin() {
        std::lock_guard<std::mutex> lock(_mutex);
        return _deque.begin();
    }

    iterator end() {
        std::lock_guard<std::mutex> lock(_mutex);
        return _deque.end();
    }
};

}

#endif //UTIL_SAFE_DEQUE_H
