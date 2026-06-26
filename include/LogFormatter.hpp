//
// Created by shahk on 26-06-2026.
//

#ifndef CONCURRENTLOGGER_LOGFORMATTER_HPP
#define CONCURRENTLOGGER_LOGFORMATTER_HPP

#pragma once
#include <string>
#include "LogMessage.hpp"

class LogFormatter {
public:
    static std::string format(const LogMessage& log);

private:
    static std::string levelToString(LogLevel level);
    static std::string formatTimestamp(
        const std::chrono::system_clock::time_point& tp);
};

#endif //CONCURRENTLOGGER_LOGFORMATTER_HPP