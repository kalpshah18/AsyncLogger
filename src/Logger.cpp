//
// Created by shahk on 26-06-2026.
//

#include "../include/Logger.hpp"

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
    : running_(true),
      logFile_("application.log", std::ios::out | std::ios::app)
{
    workerThread_ = std::thread(&Logger::processLogs, this);
}

Logger::~Logger()
{
    running_ = false;

    queue_.shutdown();

    if (workerThread_.joinable())
        workerThread_.join();

    if (logFile_.is_open())
        logFile_.close();
}

void Logger::log(
    LogLevel level,
    const std::string& message,
    const char* file,
    int line)
{
    queue_.push(
        LogMessage(
            level,
            message,
            file,
            line));
}

void Logger::trace(
    const std::string& message,
    const char* file,
    int line)
{
    log(LogLevel::Trace, message, file, line);
}

void Logger::debug(
    const std::string& message,
    const char* file,
    int line)
{
    log(LogLevel::Debug, message, file, line);
}

void Logger::info(
    const std::string& message,
    const char* file,
    int line)
{
    log(LogLevel::Info, message, file, line);
}

void Logger::warn(
    const std::string& message,
    const char* file,
    int line)
{
    log(LogLevel::Warn, message, file, line);
}

void Logger::error(
    const std::string& message,
    const char* file,
    int line)
{
    log(LogLevel::Error, message, file, line);
}

void Logger::fatal(
    const std::string& message,
    const char* file,
    int line)
{
    log(LogLevel::Fatal, message, file, line);
}

void Logger::processLogs()
{
    LogMessage message(LogLevel::Info, "", "", 0);

    while (queue_.pop(message))
    {
        logFile_
            << LogFormatter::format(message)
            << '\n';
    }

    logFile_.flush();
}