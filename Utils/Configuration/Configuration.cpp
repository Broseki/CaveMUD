//
// Created by Travis Canning on 10/14/22.
//

#include "Configuration.h"

#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

Configuration::Configuration(std::string configuration_file_path) {
    // Get the configuration data from the file
    std::ifstream f(configuration_file_path);
    json data = json::parse(f);

    // Set the configuration model properties
    // Thread Settings
    this->connection_establishment_handler_thread_count =
            data["thread_settings"]["connection_establishment_handler_thread_count"].get<uint32_t>();
    this->player_session_socket_handler_thread_count =
            data["thread_settings"]["player_session_socket_handler_thread_count"].get<uint32_t>();
    this->game_loop_thread_count =
            data["thread_settings"]["game_loop_thread_count"].get<uint32_t>();

    // Networking Settings
    this->game_port =
            data["networking_settings"]["game_port"].get<uint16_t>();
    this->connection_queue_size =
            data["networking_settings"]["connection_queue_size"].get<int>();
    this->socket_buffer_size =
            data["networking_settings"]["socket_buffer_size"].get<uint32_t>();

    // Game Settings
    this->max_players =
            data["game_settings"]["max_players"].get<uint32_t>();
    this->world_id =
            data["game_settings"]["world_id"].get<uint32_t>();
    this->tick_rate =
            data["game_settings"]["tick_rate"].get<uint32_t>();

    // System Settings
    this->log_level =
            data["system_settings"]["log_level"].get<std::string>();
}

std::string Configuration::toString() const {
    return std::string("\nServer Configuration:") +
           std::string("\n  Thread Settings:") +
           std::string("\n    Connection Establishment Handler Thread Count: ") + std::to_string(connection_establishment_handler_thread_count) +
           std::string("\n    Player Session Socket Handler Thread Count: ") + std::to_string(player_session_socket_handler_thread_count) +
           std::string("\n    Game Loop Thread Count: ") + std::to_string(game_loop_thread_count) +
           std::string("\n  Networking Settings:") +
           std::string("\n    Game Port: ") + std::to_string(game_port) +
           std::string("\n    Connection Queue Size: ") + std::to_string(connection_queue_size) +
           std::string("\n    Socket Buffer Size: ") + std::to_string(socket_buffer_size) +
           std::string("\n  Game Settings:") +
           std::string("\n    Max Players: ") + std::to_string(max_players) +
           std::string("\n    World ID: ") + std::to_string(world_id) +
           std::string("\n    Tick Rate: ") + std::to_string(tick_rate) +
           std::string("\n  System Settings:") +
           std::string("\n    log_level: ") + log_level;
}
