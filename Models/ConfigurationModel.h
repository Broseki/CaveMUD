/**
 * Representation of the server configuration file.
 */

#ifndef CAVEMUD_CONFIGURATIONMODEL_H
#define CAVEMUD_CONFIGURATIONMODEL_H

#include <cstdint>
#include <string>

class ConfigurationModel {
public:
    // Thread settings
    uint32_t connection_establishment_handler_thread_count;
    uint32_t player_session_socket_handler_thread_count;
    uint32_t game_loop_thread_count;

    // Networking settings
    uint16_t game_port;

    // Game settings
    uint32_t max_players;
    uint32_t world_id;
    uint32_t tick_rate; // Ticks per second

    // Development Settings
    std::string log_level;

    // String representation of the configuration model
    std::string toString() const;
};

#endif //CAVEMUD_CONFIGURATIONMODEL_H
