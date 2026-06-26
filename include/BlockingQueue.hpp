//
// Created by shahk on 26-06-2026.
//

#ifndef CONCURRENTLOGGER_BLOCKINGQUEUE_HPP
#define CONCURRENTLOGGER_BLOCKINGQUEUE_HPP

#pragma once
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>

template <typename T> class BlockingQueue {
public:
    BlockingQueue();
    ~BlockingQueue();

    void push()(const T& item);
    void push(T&& item);

    bool pop(T& item);
    void shutdown();

    bool empty() const;
    std::size_t size() const;

private:
    mutable std::mutex _mutex;
    std::condition_variable _cond;
    std::queue<T> _queue;
    bool _shutdown;
};

#include "BlockingQueue.hpp"

#endif //CONCURRENTLOGGER_BLOCKINGQUEUE_HPP