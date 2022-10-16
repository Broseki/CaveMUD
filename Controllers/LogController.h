//
// Created by Travis Canning on 10/14/22.
//

#ifndef CAVEMUD_LOGCONTROLLER_H
#define CAVEMUD_LOGCONTROLLER_H

#include <string>

class LogController {
private:
    std::ostream *output_stream;

public:
    enum LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    LogController(std::ostream* output_stream, LogLevel log_level);
    void log(LogLevel log_level, std::string message);

private:
    LogLevel log_level;

public:
    static std::string log_level_to_string(LogLevel log_level);
    static LogLevel string_to_log_level(std::string log_level_string);
};


#endif //CAVEMUD_LOGCONTROLLER_H
