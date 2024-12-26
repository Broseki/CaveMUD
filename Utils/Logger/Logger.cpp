//
// Created by Travis Canning on 10/14/22.
//

#include "Logger.h"

#include <cstring>
#include <iostream>
#include <algorithm>

Logger::Logger(std::ostream *output_stream, LogLevel level) {
    this->m_log_level = level;
    this->m_output_stream = output_stream;
}

std::string Logger::log_level_to_string(LogLevel level) {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}

Logger::LogLevel Logger::string_to_log_level(std::string log_level_string) {
    // Convert the string to uppercase
    std::transform(log_level_string.begin(), log_level_string.end(), log_level_string.begin(), ::toupper);

    if (log_level_string == "DEBUG") {
        return DEBUG;
    } else if (log_level_string == "INFO") {
        return INFO;
    } else if (log_level_string == "WARNING") {
        return WARNING;
    } else if (log_level_string == "ERROR") {
        return ERROR;
    } else if (log_level_string == "FATAL") {
        return FATAL;
    } else {
        return DEBUG;
    }
}

void Logger::log(LogLevel level, std::string message) {
    // Lock the log mutex safely (RAII)
    const std::lock_guard<std::mutex> lock(m_log_mutex);

    // Check if the log level is high enough to log the message
    if (level >= this->m_log_level) {
        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(now);

        // Construct the message
        std::string log_message = "[";
        log_message += log_level_to_string(level);
        log_message += " - ";
        log_message += strtok(std::ctime(&current_time), "\n");
        log_message += "] : ";
        log_message += message;

        // Write the message to the output stream
        *m_output_stream << log_message << std::endl;
    }
}
