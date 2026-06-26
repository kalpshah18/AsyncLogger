//
// Created by shahk on 26-06-2026.
//

#include <thread>
#include <vector>

#include "../include/Logger.hpp"

int main()
{
    const int numThreads = 10;
    const int logsPerThread = 1000;

    std::vector<std::thread> threads;

    for(int i = 0; i < numThreads; i++)
    {
        threads.emplace_back([i]()
        {
            for(int j = 0; j < logsPerThread; j++)
            {
                LOG_INFO(
                    "Thread " +
                    std::to_string(i) +
                    " Log " +
                    std::to_string(j));
            }
        });
    }

    for(auto& t : threads)
        t.join();

    return 0;
}