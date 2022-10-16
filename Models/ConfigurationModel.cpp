/**
 * Representation of the server configuration file.
 */

#include "ConfigurationModel.h"

std::string ConfigurationModel::toString() const {
return std::string("\nServer Configuration:") +
        std::string("\n  Thread Settings:") +
        std::string("\n    Connection Establishment Handler Thread Count: ") + std::to_string(connection_establishment_handler_thread_count) +
        std::string("\n    Player Session Socket Handler Thread Count: ") + std::to_string(player_session_socket_handler_thread_count) +
        std::string("\n    Game Loop Thread Count: ") + std::to_string(game_loop_thread_count) +
        std::string("\n  Networking Settings:") +
        std::string("\n    Game Port: ") + std::to_string(game_port) +
        std::string("\n  Game Settings:") +
        std::string("\n    Max Players: ") + std::to_string(max_players) +
        std::string("\n    World ID: ") + std::to_string(world_id) +
        std::string("\n    Tick Rate: ") + std::to_string(tick_rate) +
        std::string("\n  System Settings:") +
        std::string("\n    log_level: ") + log_level;
}