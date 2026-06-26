//
// Created by shahk on 26-06-2026.
//

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "../include/Logger.hpp"

int main()
{
    constexpr int THREADS = 128;
    constexpr int LOGS = 100000;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> workers;

    for(int i = 0; i < THREADS; i++)
    {
        workers.emplace_back([]
        {
            for(int j = 0; j < LOGS; j++)
            {
                LOG_INFO("Benchmark log");
            }
        });
    }

    for(auto& t : workers)
        t.join();

    auto end = std::chrono::high_resolution_clock::now();

    double seconds =
        std::chrono::duration<double>(end - start).count();

    long long totalLogs =
        static_cast<long long>(THREADS) * LOGS;

    std::cout
        << "Threads: " << THREADS << '\n'
        << "Logs: " << totalLogs << '\n'
        << "Time: " << seconds << " sec\n"
        << "Throughput: "
        << totalLogs / seconds
        << " logs/sec\n";
}