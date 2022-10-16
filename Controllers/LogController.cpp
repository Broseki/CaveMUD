//
// Created by Travis Canning on 10/14/22.
//

#include "LogController.h"

#include <chrono>
#include <iostream>

LogController::LogController(std::ostream *output_stream, LogLevel log_level) {
    this->log_level = log_level;
    this->output_stream = output_stream;
}

std::string LogController::log_level_to_string(LogLevel log_level) {
    switch (log_level) {
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

LogController::LogLevel LogController::string_to_log_level(std::string log_level_string) {
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

void LogController::log(LogLevel log_level, std::string message) {
    // Check if the log level is high enough to log the message
    if (log_level >= this->log_level) {

        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(now);

        // Construct the message
        std::string log_message = "[";
        log_message += log_level_to_string(log_level);
        log_message += " - ";
        log_message += strtok(std::ctime(&current_time), "\n");
        log_message += "] : ";
        log_message += message;

        // Write the message to the output stream
        *output_stream << log_message << std::endl;
    }
}
