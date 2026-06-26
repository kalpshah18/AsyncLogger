//
// Created by shahk on 26-06-2026.
//

#ifndef CONCURRENTLOGGER_BLOCKINGQUEUE_TPP
#define CONCURRENTLOGGER_BLOCKINGQUEUE_TPP

#pragma once
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


#endif //CONCURRENTLOGGER_BLOCKINGQUEUE_TPP