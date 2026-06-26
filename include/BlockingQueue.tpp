//
// Created by shahk on 26-06-2026.
//

#ifndef CONCURRENTLOGGER_BLOCKINGQUEUE_TPP
#define CONCURRENTLOGGER_BLOCKINGQUEUE_TPP

#pragma once
#include <mutex>
#include <queue>

template<typename T> BlockingQueue<T>::BlockingQueue() : _shutdown(false) {
}

template<typename T> BlockingQueue<T>::~BlockingQueue() {
    shutdown();
}

template<typename T> void BlockingQueue<T>::push(const T& item) {
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_shutdown) return;
        _queue.push(item);
    }

    _cond.notify_one();
}

template<typename T> void BlockingQueue<T>::push(T&& item) {
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_shutdown) return;
        _queue.push(std::move(item));
    }

    _cond.notify_one();
}

template<typename T> bool BlockingQueue<T>::pop(T& item) {
    std::unique_lock<std::mutex> lock(_mutex);

    _cond.wait(lock, [this] {
        return _shutdown || !_queue.empty();
    });

    if (_shutdown && _queue.empty()) return false;
    item = std::move(_queue.front());
    _queue.pop();
    return true;
}

template<typename T> void BlockingQueue<T>::shutdown()
{
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _shutdown = true;
    }

    _cond.notify_all();
}

template<typename T> bool BlockingQueue<T>::empty() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.empty();
}

template<typename T>
std::size_t BlockingQueue<T>::size() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.size();
}
#endif //CONCURRENTLOGGER_BLOCKINGQUEUE_TPP