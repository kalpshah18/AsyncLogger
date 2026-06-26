//
// Created by shahk on 26-06-2026.
//

#include "../include/LogFormatter.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string LogFormatter::format(const LogMessage& log){
    std::ostringstream oss;
    oss << formatTimestamp(log.timestamp)
        << " ["
        << levelToString(log.level)
        << "] "
        << "[TID "
        << log.thread_id
        << "] "
        << log.file
        << ":"
        << log.line
        << " "
        << log.message;
    return oss.str();
}

std::string LogFormatter::levelToString(LogLevel level)
{
    switch (level)
    {
        case LogLevel::Trace:
            return "TRACE";

        case LogLevel::Debug:
            return "DEBUG";

        case LogLevel::Info:
            return "INFO";

        case LogLevel::Warn:
            return "WARN";

        case LogLevel::Error:
            return "ERROR";

        case LogLevel::Fatal:
            return "FATAL";

        default:
            return "UNKNOWN";
    }
}

std::string LogFormatter::formatTimestamp(const std::chrono::system_clock::time_point& tp) {
    using namespace std::chrono;

    auto time = system_clock::to_time_t(tp);

    std::tm tm;

#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif

    auto ms =
        duration_cast<milliseconds>(
            tp.time_since_epoch()) %
        1000;

    std::ostringstream oss;

    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << '.'
        << std::setfill('0')
        << std::setw(3)
        << ms.count();

    return oss.str();
}