#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../Utils/Configuration/Configuration.h"
#include "../../Utils/Logger/Logger.h"
#include "../../Session/Session.h"
#include "../../Session/Sessions.h"
#include <memory>

class SessionsTest : public ::testing::Test {
protected:
    SessionsTest() : logger(Logger::initialize(&std::cout, Logger::INFO)), configuration(Configuration::initialize("test_config.json")), sessions(configuration, logger) {}

    Logger* logger;
    Configuration* configuration;
    Sessions sessions;

public:

    void TearDown() override {
        testing::Mock::VerifyAndClearExpectations(logger);
    }

    static void TearDownTestSuite() {
        Logger::destroy();
    }

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
    std::vector<std::weak_ptr<Session>> weak_refs;
    {
        Sessions *tmp_sessions = new Sessions(configuration, logger);

        // Store weak references to track Session lifetime
        auto session1 = std::make_shared<Session>(0);
        auto session2 = std::make_shared<Session>(0);
        auto session3 = std::make_shared<Session>(0);

        weak_refs.push_back(session1);
        weak_refs.push_back(session2);
        weak_refs.push_back(session3);

        tmp_sessions->addSession(session1);
        tmp_sessions->addSession(session2);
        tmp_sessions->addSession(session3);

        delete tmp_sessions;
    }

    // Verify all sessions were destroyed
    for (const auto& weak_ref : weak_refs) {
        EXPECT_TRUE(weak_ref.expired()) << "Session was not properly destroyed";
    }
}

TEST_F(SessionsTest, AddSessionFull) {
    for (uint32_t i = 0; i < configuration->max_players; i++) {
        sessions.addSession(std::make_shared<Session>(i));
    }

    EXPECT_THROW(sessions.addSession(std::make_shared<Session>(0)), std::runtime_error);
}