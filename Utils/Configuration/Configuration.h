//
// Created by Travis Canning on 10/14/22.
//

#ifndef CAVEMUD_CONFIGURATION_H
#define CAVEMUD_CONFIGURATION_H

#include <string>
#include <cstdint>

class Configuration {

public:
    Configuration(std::string configuration_file_path);

    // String representation of the configuration model
    std::string toString() const;

public:
    // Thread settings
    uint32_t connection_establishment_handler_thread_count;
    uint32_t player_session_socket_handler_thread_count;
    uint32_t game_loop_thread_count;

    // Networking settings
    uint16_t game_port;
    int connection_queue_size;
    uint32_t socket_buffer_size;

    // Game settings
    uint32_t max_players;
    uint32_t world_id;
    uint32_t tick_rate; // Ticks per second

    // Development Settings
    std::string log_level;
};


#endif //CAVEMUD_CONFIGURATION_H
