#include <iostream>
#include <vector>
#include <thread>
#include "Utils/Configuration/Configuration.h"
#include "Utils/Logger/Logger.h"
#include "Networking/Server/ServerListener.h"
#include "Networking/Server/ServerSocket.h"
#include "Engine/MasterClock.h"
#include "Session/SessionHandler.h"
#include "Engine/GameLoop.h"

int main(int argc, char** argv) {
    std::cout << "+-------------------------------------+" << std::endl;
    std::cout << "| CaveTEK - Multi User Dungeon Engine |" << std::endl;
    std::cout << "|            Version 0.2.0            |" << std::endl;
    std::cout << "|    (c) 2014 - 2022 - CaveFox LLC    |" << std::endl;
    std::cout << "+-------------------------------------+" << std::endl;

    // Load settings from config file passed in as an argument
    // If no argument is passed, load default config file (config.json)
    if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " [config_file]" << std::endl;
        return 1;
    }
    Configuration configuration = Configuration(argc == 2 ? argv[1] : "config.json");

    // Create a log controller
    Logger logger = Logger(&std::cout, logger.string_to_log_level(configuration.log_level));
    logger.log(logger.INFO, "Logger initialized... Starting server...");

    // Print the configuration model
    logger.log(logger.DEBUG, configuration.toString());

    // Initialize a vector of threads to track all the threads we create
    std::vector<std::thread> threads;

    // Initialize the main server socket
    ServerSocket server_socket = ServerSocket(&configuration, &logger);

    // Start the client socket handler threads
    Sessions sessions = Sessions(&configuration, &logger);

    // Create server listener threads
    for (uint32_t i = 0; i < configuration.connection_establishment_handler_thread_count; i++) {
        threads.emplace_back(std::thread(&ServerListener::start, new ServerListener(&logger, &server_socket, &configuration, &sessions)));
    }

    // Setup Master Clock
    MasterClock master_clock = MasterClock(&logger, configuration.player_session_socket_handler_thread_count, configuration.game_loop_thread_count);

    // Start session handler threads
    for (uint32_t i = 0; i < configuration.player_session_socket_handler_thread_count; i++) {
        threads.emplace_back(std::thread(&SessionHandler::start, new SessionHandler(&logger, &configuration, &master_clock, &sessions, i)));
    }

    // Start game loop threads
    for (uint32_t i = 0; i < configuration.game_loop_thread_count; i++) {
        threads.emplace_back(std::thread(&GameLoop::start, new GameLoop(&logger, &configuration, &master_clock, &sessions, i)));
    }

    logger.log(logger.INFO, "Server started successfully!");

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
