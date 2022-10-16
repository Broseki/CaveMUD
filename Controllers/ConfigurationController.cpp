//
// Created by Travis Canning on 10/14/22.
//

#include "ConfigurationController.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

ConfigurationModel ConfigurationController::getConfiguration(std::string configuration_file_path) {
    // Create a new configuration model
    ConfigurationModel configuration_model;

    // Get the configuration data from the file
    std::ifstream f(configuration_file_path);
    json data = json::parse(f);

    // Set the configuration model properties
    // Thread Settings
    configuration_model.connection_establishment_handler_thread_count =
            data["thread_settings"]["connection_establishment_handler_thread_count"].get<uint32_t>();
    configuration_model.player_session_socket_handler_thread_count =
            data["thread_settings"]["player_session_socket_handler_thread_count"].get<uint32_t>();
    configuration_model.game_loop_thread_count =
            data["thread_settings"]["game_loop_thread_count"].get<uint32_t>();

    // Networking Settings
    configuration_model.game_port =
            data["networking_settings"]["game_port"].get<uint16_t>();
    configuration_model.connection_queue_size =
            data["networking_settings"]["connection_queue_size"].get<int>();

    // Game Settings
    configuration_model.max_players =
            data["game_settings"]["max_players"].get<uint32_t>();
    configuration_model.world_id =
            data["game_settings"]["world_id"].get<uint32_t>();
    configuration_model.tick_rate =
            data["game_settings"]["tick_rate"].get<uint32_t>();

    // System Settings
    configuration_model.log_level =
            data["system_settings"]["log_level"].get<std::string>();

    // Return the configuration model
    return configuration_model;
}
