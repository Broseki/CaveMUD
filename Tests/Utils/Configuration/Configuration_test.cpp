#include "gtest/gtest.h"
#include "../../../Utils/Configuration/Configuration.h"

class ConfigurationTest : public ::testing::Test {
protected:
    ConfigurationTest() : configuration("test_config.json") {}
    Configuration configuration;
};

TEST_F(ConfigurationTest, ThreadSettings) {
    EXPECT_EQ(configuration.connection_establishment_handler_thread_count, 43432);
    EXPECT_EQ(configuration.player_session_socket_handler_thread_count, 5452);
    EXPECT_EQ(configuration.game_loop_thread_count, 3425);
}

TEST_F(ConfigurationTest, NetworkingSettings) {
    EXPECT_EQ(configuration.game_port, 11111);
    EXPECT_EQ(configuration.connection_queue_size, 5);
    EXPECT_EQ(configuration.socket_buffer_size, 1000);
}

TEST_F(ConfigurationTest, GameSettings) {
    EXPECT_EQ(configuration.max_players, 10);
    EXPECT_EQ(configuration.world_id, 112);
    EXPECT_EQ(configuration.tick_rate, 12);
}

TEST_F(ConfigurationTest, SystemSettings) {
    EXPECT_EQ(configuration.log_level, "debug");
}

TEST_F(ConfigurationTest, ToString) {
    std::string expected_output =
            "\nServer Configuration:"
            "\n  Thread Settings:"
            "\n    Connection Establishment Handler Thread Count: 43432"
            "\n    Player Session Socket Handler Thread Count: 5452"
            "\n    Game Loop Thread Count: 3425"
            "\n  Networking Settings:"
            "\n    Game Port: 11111"
            "\n    Connection Queue Size: 5"
            "\n    Socket Buffer Size: 1000"
            "\n  Game Settings:"
            "\n    Max Players: 10"
            "\n    World ID: 112"
            "\n    Tick Rate: 12"
            "\n  System Settings:"
            "\n    log_level: debug";

    EXPECT_EQ(configuration.toString(), expected_output);
}