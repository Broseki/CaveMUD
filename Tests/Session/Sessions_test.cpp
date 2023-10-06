#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../Utils/Configuration/Configuration.h"
#include "../../Utils/Logger/Logger.h"
#include "../../Session/Session.h"
#include "../../Session/Sessions.h"
#include <memory>

class MockLogger : public Logger {
public:
    MockLogger(std::ostream* output_stream, LogLevel level) : Logger(output_stream, level) {}
    MOCK_METHOD(void, log, (LogLevel level, std::string message), (override));
};

class SessionsTest : public ::testing::Test {
protected:
    SessionsTest() : configuration("test_config.json"), logger(&std::cout, Logger::FATAL), sessions(&configuration, &logger) {}

    Configuration configuration;
    Logger logger;
    Sessions sessions;
};

TEST_F(SessionsTest, AddSession) {
    // Create a new session
    auto session = std::make_shared<Session>(0);

    // Add the session to the sessions object
    sessions.addSession(session);

    // Check that the sessions object contains the session
    EXPECT_EQ(sessions.getNumSessions(), 1);
    EXPECT_EQ(sessions.getSessions(0, 1)[0], session);
}

TEST_F(SessionsTest, RemoveSession) {
    // Create a new session
    auto session = std::make_shared<Session>(0);

    // Add the session to the sessions object
    sessions.addSession(session);

    // Remove the session from the sessions object
    sessions.removeSession(session->get_socketfd(), false);

    // Check that the sessions object no longer contains the session
    EXPECT_EQ(sessions.getNumSessions(), 0);
}

TEST_F(SessionsTest, GetNumSessionsWithOneSession) {
    // Check that the number of sessions is initially zero
    EXPECT_EQ(sessions.getNumSessions(), 0);

    // Create a new session
    auto session = std::make_shared<Session>(0);

    // Add the session to the sessions object
    sessions.addSession(session);

    // Check that the number of sessions is now one
    EXPECT_EQ(sessions.getNumSessions(), 1);
}

TEST_F(SessionsTest, GetNumSessionsWithMultipleSessions) {
    // Check that the number of sessions is initially zero
    EXPECT_EQ(sessions.getNumSessions(), 0);

    // Create three new sessions
    auto session1 = std::make_shared<Session>(0);
    auto session2 = std::make_shared<Session>(1);
    auto session3 = std::make_shared<Session>(2);

    // Add the sessions to the sessions object
    sessions.addSession(session1);
    sessions.addSession(session2);
    sessions.addSession(session3);

    // Check that the number of sessions is now three
    EXPECT_EQ(sessions.getNumSessions(), 3);
}

TEST_F(SessionsTest, GetSessions) {
    // Create three new sessions
    auto session1 = std::make_shared<Session>(0);
    auto session2 = std::make_shared<Session>(1);
    auto session3 = std::make_shared<Session>(2);

    // Add the sessions to the sessions object
    sessions.addSession(session1);
    sessions.addSession(session2);
    sessions.addSession(session3);

    // Check that the sessions object returns the correct sessions
    EXPECT_EQ(sessions.getSessions(0, 3).size(), 1);
    EXPECT_EQ(sessions.getSessions(1, 3).size(), 1);
    EXPECT_EQ(sessions.getSessions(2, 3).size(), 1);
    EXPECT_EQ(sessions.getSessions(0, 2).size(), 2);
    EXPECT_EQ(sessions.getSessions(1, 2).size(), 1);
}

TEST_F(SessionsTest, RemoveNonExistentSession) {
    // Create a new session
    auto session = std::make_shared<Session>(0);

    // Add the session to the sessions object
    sessions.addSession(session);

    // Remove a non-existent session from the sessions object
    sessions.removeSession(12345, false);

    // Check that the sessions object still contains the original session
    EXPECT_EQ(sessions.getNumSessions(), 1);
    EXPECT_EQ(sessions.getSessions(0, 1)[0], session);
}

TEST_F(SessionsTest, Destructor) {
    // Expect the logger to be called with the correct message
    MockLogger logger_tmp(&std::cout, Logger::INFO);
    EXPECT_CALL(logger_tmp, log(Logger::INFO, "Destroying Sessions object")).Times(1);

    Sessions *tmp_sessions = new Sessions(&configuration, &logger_tmp);

    tmp_sessions->addSession(std::make_shared<Session>(0));
    tmp_sessions->addSession(std::make_shared<Session>(0));
    tmp_sessions->addSession(std::make_shared<Session>(0));

    delete tmp_sessions;
}

TEST_F(SessionsTest, AddSessionFull) {
    for (uint32_t i = 0; i < configuration.max_players; i++) {
        sessions.addSession(std::make_shared<Session>(i));
    }

    EXPECT_THROW(sessions.addSession(std::make_shared<Session>(0)), std::runtime_error);
}