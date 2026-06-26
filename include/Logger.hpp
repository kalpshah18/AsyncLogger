//
// Created by shahk on 26-06-2026.
//

#ifndef CONCURRENTLOGGER_LOGGER_HPP
#define CONCURRENTLOGGER_LOGGER_HPP

#pragma once

#include <atomic>
#include <fstream>
#include <string>
#include <thread>

#include "BlockingQueue.hpp"
#include "LogFormatter.hpp"
#include "LogMessage.hpp"

class Logger
{
public:
    static Logger& instance();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(
        LogLevel level,
        const std::string& message,
        const char* file,
        int line);

    void trace(const std::string& message,
               const char* file,
               int line);

    void debug(const std::string& message,
               const char* file,
               int line);

    void info(const std::string& message,
              const char* file,
              int line);

    void warn(const std::string& message,
              const char* file,
              int line);

    void error(const std::string& message,
               const char* file,
               int line);

    void fatal(const std::string& message,
               const char* file,
               int line);

private:
    Logger();
    ~Logger();

    void processLogs();

private:
    std::atomic<bool> running_;

    BlockingQueue<LogMessage> queue_;

    std::thread workerThread_;

    std::ofstream logFile_;
};

#define LOG_TRACE(msg) Logger::instance().trace(msg, __FILE__, __LINE__)

#define LOG_DEBUG(msg) Logger::instance().debug(msg, __FILE__, __LINE__)

#define LOG_INFO(msg) Logger::instance().info(msg, __FILE__, __LINE__)

#define LOG_WARN(msg) Logger::instance().warn(msg, __FILE__, __LINE__)

#define LOG_ERROR(msg) Logger::instance().error(msg, __FILE__, __LINE__)

#define LOG_FATAL(msg) Logger::instance().fatal(msg, __FILE__, __LINE__)

#endif //CONCURRENTLOGGER_LOGGER_HPP