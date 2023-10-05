#include <gtest/gtest.h>
#include <sstream>
#include "../../../Utils/Logger/Logger.h"

using namespace testing;

class LoggerTest : public Test {
public:
    std::ostringstream output_stream;
    Logger logger{&output_stream, Logger::DEBUG};
};

TEST_F(LoggerTest, LogLevelToString) {
    // Test
    EXPECT_EQ(Logger::log_level_to_string(Logger::DEBUG), "DEBUG");
    EXPECT_EQ(Logger::log_level_to_string(Logger::INFO), "INFO");
    EXPECT_EQ(Logger::log_level_to_string(Logger::WARNING), "WARNING");
    EXPECT_EQ(Logger::log_level_to_string(Logger::ERROR), "ERROR");
    EXPECT_EQ(Logger::log_level_to_string(Logger::FATAL), "FATAL");
    EXPECT_EQ(Logger::log_level_to_string(static_cast<Logger::LogLevel>(100)), "UNKNOWN");
}

TEST_F(LoggerTest, StringToLogLevel) {
    // Test
    EXPECT_EQ(Logger::string_to_log_level("DEBUG"), Logger::DEBUG);
    EXPECT_EQ(Logger::string_to_log_level("INFO"), Logger::INFO);
    EXPECT_EQ(Logger::string_to_log_level("WARNING"), Logger::WARNING);
    EXPECT_EQ(Logger::string_to_log_level("ERROR"), Logger::ERROR);
    EXPECT_EQ(Logger::string_to_log_level("FATAL"), Logger::FATAL);
    EXPECT_EQ(Logger::string_to_log_level("UNKNOWN"), Logger::DEBUG);
}

TEST_F(LoggerTest, LogDebug) {
    // Setup
    std::string message = "Debug message";
    logger.log(Logger::DEBUG, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[DEBUG - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogInfo) {
    // Setup
    std::string message = "Info message";
    logger.log(Logger::INFO, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[INFO - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogWarning) {
    // Setup
    std::string message = "Warning message";
    logger.log(Logger::WARNING, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[WARNING - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogError) {
    // Setup
    std::string message = "Error message";
    logger.log(Logger::ERROR, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[ERROR - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogFatal) {
    // Setup
    std::string message = "Fatal message";
    logger.log(Logger::FATAL, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[FATAL - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogUnknownLogLevel) {
    // Setup
    std::string message = "Unknown log level message";
    logger.log(static_cast<Logger::LogLevel>(100), message);

    // Test
    EXPECT_EQ(output_stream.str().find("[UNKNOWN - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogLevelDebug) {
    // Setup
    Logger logger_tmp{&output_stream, Logger::DEBUG};
    std::string message = "Test message";

    // Test
    logger_tmp.log(Logger::DEBUG, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
    
    logger_tmp.log(Logger::INFO, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::WARNING, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::ERROR, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogLevelInfo) {
    // Setup
    Logger logger_tmp{&output_stream, Logger::INFO};
    std::string message = "Test message";

    // Test
    logger_tmp.log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger_tmp.log(Logger::INFO, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::WARNING, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::ERROR, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogLevelWarning) {
    // Setup
    Logger logger_tmp{&output_stream, Logger::WARNING};
    std::string message = "Test message";

    // Test
    logger_tmp.log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger_tmp.log(Logger::INFO, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::WARNING, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::ERROR, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogLevelError) {
    // Setup
    Logger logger_tmp{&output_stream, Logger::ERROR};
    std::string message = "Test message";

    // Test
    logger_tmp.log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger_tmp.log(Logger::INFO, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::WARNING, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::ERROR, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogLevelFatal) {
    // Setup
    Logger logger_tmp{&output_stream, Logger::FATAL};
    std::string message = "Test message";

    // Test
    logger_tmp.log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger_tmp.log(Logger::INFO, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::WARNING, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::ERROR, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger_tmp.log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
}

TEST_F(LoggerTest, LogLevelUnknown) {
    // Setup
    Logger logger_tmp{&output_stream, static_cast<Logger::LogLevel>(100)};
    std::string message = "Test message";

    // Test
    logger_tmp.log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger_tmp.log(Logger::INFO, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::WARNING, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::ERROR, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(Logger::FATAL, message);
    EXPECT_EQ(output_stream.str(), "");

    logger_tmp.log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    EXPECT_NE(1,1);
}