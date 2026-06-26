cmake_minimum_required(VERSION 3.16)

project(ConcurrentLogger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Logger library
add_library(ConcurrentLoggerLib
        src/Logger.cpp
        src/LogFormatter.cpp
)

target_include_directories(ConcurrentLoggerLib
        PUBLIC include
)

# Example executable
add_executable(LoggerExample
        examples/main.cpp
)

target_link_libraries(LoggerExample
        PRIVATE ConcurrentLoggerLib
)

# Benchmark executable
add_executable(LoggerBenchmark
        benchmark/benchmark.cpp
)

target_link_libraries(LoggerBenchmark
        PRIVATE ConcurrentLoggerLib
)