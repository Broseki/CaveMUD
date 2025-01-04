#include <gtest/gtest.h>
#include <sstream>
#include "../../../Utils/Logger/Logger.h"

using namespace testing;

class LoggerTest : public Test {
public:
    std::ostringstream output_stream;

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
    Logger *logger = Logger::initialize(&output_stream, Logger::DEBUG);
    std::string message = "Debug message";
    logger->log(Logger::DEBUG, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[DEBUG - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogInfo) {
    // Setup
    Logger *logger = Logger::initialize(&output_stream, Logger::DEBUG);
    std::string message = "Info message";
    logger->log(Logger::INFO, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[INFO - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogWarning) {
    // Setup
    Logger *logger = Logger::initialize(&output_stream, Logger::DEBUG);
    std::string message = "Warning message";
    logger->log(Logger::WARNING, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[WARNING - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogError) {
    // Setup
    Logger *logger = Logger::initialize(&output_stream, Logger::DEBUG);
    std::string message = "Error message";
    logger->log(Logger::ERROR, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[ERROR - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogFatal) {
    // Setup
    Logger *logger = Logger::initialize(&output_stream, Logger::DEBUG);
    std::string message = "Fatal message";
    logger->log(Logger::FATAL, message);

    // Test
    EXPECT_EQ(output_stream.str().find("[FATAL - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogUnknownLogLevel) {
    // Setup
    Logger *logger = Logger::initialize(&output_stream, Logger::DEBUG);
    std::string message = "Unknown log level message";
    logger->log(static_cast<Logger::LogLevel>(100), message);

    // Test
    EXPECT_EQ(output_stream.str().find("[UNKNOWN - "), 0);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogLevelDebug) {
    // Setup
    Logger *logger = Logger::initialize(&output_stream, Logger::DEBUG);
    std::string message = "Test message";

    // Test
    logger->log(Logger::DEBUG, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);
    
    logger->log(Logger::INFO, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::WARNING, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::ERROR, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogLevelInfo) {
    // Setup
    Logger* logger = Logger::initialize(&output_stream, Logger::INFO);
    std::string message = "Test message";

    // Test
    logger->log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger->log(Logger::INFO, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::WARNING, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::ERROR, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogLevelWarning) {
    // Setup
    Logger* logger = Logger::initialize(&output_stream, Logger::WARNING);
    std::string message = "Test message";

    // Test
    logger->log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger->log(Logger::INFO, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::WARNING, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::ERROR, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogLevelError) {
    // Setup
    Logger* logger = Logger::initialize(&output_stream, Logger::ERROR);
    std::string message = "Test message";

    // Test
    logger->log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger->log(Logger::INFO, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::WARNING, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::ERROR, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogLevelFatal) {
    // Setup
    Logger *logger = Logger::initialize(&output_stream, Logger::FATAL);
    std::string message = "Test message";

    // Test
    logger->log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger->log(Logger::INFO, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::WARNING, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::ERROR, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::FATAL, message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    logger->log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, LogLevelUnknown) {
    // Setup
    Logger *logger = Logger::initialize(&output_stream, static_cast<Logger::LogLevel>(100));
    std::string message = "Test message";

    // Test
    logger->log(Logger::DEBUG, message);
    EXPECT_EQ(output_stream.str(), "");
    
    logger->log(Logger::INFO, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::WARNING, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::ERROR, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(Logger::FATAL, message);
    EXPECT_EQ(output_stream.str(), "");

    logger->log(static_cast<Logger::LogLevel>(100), message);
    EXPECT_NE(output_stream.str().find(message), std::string::npos);

    // Tear down
    Logger::destroy();
}

TEST_F(LoggerTest, DuplicateInitializeCall) {
    // Call initialize twice
    Logger::initialize(&output_stream, Logger::DEBUG);
    // The first call should be successful with no warning message
    EXPECT_EQ(output_stream.str(), "");

    // Call initialize again
    Logger::initialize(&output_stream, Logger::DEBUG);
    // We should get a warning message
    EXPECT_EQ(output_stream.str().find("[WARNING - "), 0);

    // Tear down
    Logger::destroy();
}