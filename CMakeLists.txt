cmake_minimum_required(VERSION 4.0)
project(ConcurrentLogger)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConcurrentLogger main.cpp
        include/LogMessage.hpp
        include/Logger.hpp
        include/BlockingQueue.hpp
        include/BlockingQueue.hpp
        include/BlockingQueue.hpp
        include/BlockingQueue.tpp)
