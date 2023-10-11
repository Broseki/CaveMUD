#include <gtest/gtest.h>
#include "../../Session/Session.h"
#include "../../Engine/StateMachines/Echo.h"
#include <memory>
#include "boost/any.hpp"
#include "../../Engine/Views/EchoView.h"
#include "../../Session/KV_Keys.h"

#define SOCKET_FD 1337

using namespace testing;

class SessionTest: public Test {
public:
    SessionTest() : session_uut(SOCKET_FD) {}
    Session session_uut;
};

TEST_F(SessionTest, GetSocketfd) {
    // Test
    EXPECT_EQ(session_uut.get_socketfd(), SOCKET_FD);
}

TEST_F(SessionTest, SetGetInputBuffer) {
    // Setup
    std::vector<char8_t> input_buffer = {'a', 'b', 'c'};
    session_uut.set_input_buffer(input_buffer);

    // Test
    EXPECT_EQ(session_uut.get_input_buffer(), input_buffer);
}

TEST_F(SessionTest, ClearInputBuffer) {
    // Setup
    std::vector<char8_t> input_buffer = {'a', 'b', 'c'};
    session_uut.set_input_buffer(input_buffer);

    // Test to make sure we set the buffer correctly
    EXPECT_EQ(session_uut.get_input_buffer(), input_buffer);

    // Clear the buffer
    session_uut.clear_input_buffer();

    // Test to make sure the buffer was cleared
    EXPECT_EQ(session_uut.get_input_buffer().size(), 0);
}

TEST_F(SessionTest, SetGetOutputBuffer) {
    // Setup
    std::vector<char8_t> output_buffer = {'a', 'b', 'c'};
    session_uut.set_output_buffer(output_buffer);

    // Test
    EXPECT_EQ(session_uut.get_output_buffer(), output_buffer);
}

TEST_F(SessionTest, ClearOutputBuffer) {
    // Setup
    std::vector<char8_t> output_buffer = {'a', 'b', 'c'};
    session_uut.set_output_buffer(output_buffer);

    // Test to make sure we set the buffer correctly
    EXPECT_EQ(session_uut.get_output_buffer(), output_buffer);

    // Clear the buffer
    session_uut.clear_output_buffer();

    // Test to make sure the buffer was cleared
    EXPECT_EQ(session_uut.get_output_buffer().size(), 0);
}

TEST_F(SessionTest, AddRemoveStateMachine) {
    // Setup
    auto state_machine = std::make_shared<Echo>();
    Logger logger(&std::cout, Logger::FATAL);

    // Test to make sure the session doesn't have any state machines
    EXPECT_EQ(session_uut.get_state_machines().size(), 0);

    // Add the state machine
    session_uut.add_state_machine(&logger, state_machine);

    // Test to make sure the session has the state machine
    EXPECT_EQ(session_uut.get_state_machines().size(), 1);

    // Remove the state machine
    session_uut.remove_state_machine(&logger, state_machine);

    // Test to make sure the session doesn't have any state machines
    EXPECT_EQ(session_uut.get_state_machines().size(), 0);
}

TEST_F(SessionTest, GetSetKeyValue) {
    std::string key = "testkey";
    uint32_t value = 1234;

    // Test to make sure the session doesn't have the key
    EXPECT_TRUE(session_uut.get_kv(key).empty());

    // Set the key
    session_uut.set_kv(key, value);

    // Test to make sure the session has the key
    EXPECT_EQ(boost::any_cast<uint32_t>(session_uut.get_kv(key)), value);
}

TEST_F(SessionTest, RemoveKeyValue) {
    std::string key = "testkey";
    uint32_t value = 1234;

    // Set the key
    session_uut.set_kv(key, value);

    // Test to make sure the session has the key
    EXPECT_EQ(boost::any_cast<uint32_t>(session_uut.get_kv(key)), value);

    // Remove the key
    session_uut.remove_kv(key);

    // Test to make sure the session doesn't have the key
    EXPECT_TRUE(session_uut.get_kv(key).empty());
}


TEST_F(SessionTest, GetSetView) {
    Logger logger(&std::cout, Logger::FATAL);
    auto view = std::make_shared<EchoView>();

    // Test to make sure the session doesn't have a view
    EXPECT_EQ(session_uut.get_view(), nullptr);

    // Set the view
    session_uut.set_view(&logger, view);

    // Test to make sure the session has the view
    EXPECT_EQ(session_uut.get_view(), view);
}

TEST_F(SessionTest, Destroy) {
    // Make sure that the SESSION_KV_DESTROY_FLAG value is either false or not set
    EXPECT_TRUE(session_uut.get_kv(SESSION_KV_DESTROY_FLAG).empty() ||
                !boost::any_cast<bool>(session_uut.get_kv(SESSION_KV_DESTROY_FLAG)));

    // Call the destroy method
    session_uut.destroy();

    // Make sure that the SESSION_KV_DESTROY_FLAG value is true
    EXPECT_TRUE(boost::any_cast<bool>(session_uut.get_kv(SESSION_KV_DESTROY_FLAG)));

}
