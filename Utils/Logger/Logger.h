//
// Created by Travis Canning on 10/14/22.
//

#ifndef CAVEMUD_LOGGER_H
#define CAVEMUD_LOGGER_H

#include <string>
#include <mutex>

class Logger {

public:
    enum LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    Logger(const Logger&) = delete;
    virtual ~Logger() = default;
    Logger& operator=(const Logger&) = delete;

    static Logger* initialize(std::ostream *output_stream, LogLevel level);
    static Logger* get_instance();
    static void destroy();

    virtual void log(LogLevel log_level, std::string message);

protected:
    Logger(std::ostream *output_stream, LogLevel level);
    static Logger* m_instance;

private:

    LogLevel m_log_level;
    std::ostream *m_output_stream;
    std::mutex m_log_mutex;

public:
    static std::string log_level_to_string(LogLevel log_level);
    static LogLevel string_to_log_level(std::string log_level_string);
};


#endif //CAVEMUD_LOGGER_H
