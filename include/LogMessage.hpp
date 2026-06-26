//
// Created by shahk on 26-06-2026.
//

#ifndef CONCURRENTLOGGER_LOGMESSAGE_HPP
#define CONCURRENTLOGGER_LOGMESSAGE_HPP

#pragma once
#include <chrono>
#include <string>
#include <thread>

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

struct LogMessage {
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::thread::id thread_id;
    LogLevel level;
    std::string message;
    std::string file;
    int line;

    LogMessage(LogLevel level, std::string message, std::string file, int line): level(level), message(message), file(file), line(line) {}
};

#endif //CONCURRENTLOGGER_LOGMESSAGE_HPP