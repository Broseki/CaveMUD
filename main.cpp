#include <iostream>
#include <vector>
#include <thread>
#include "Models/ConfigurationModel.h"
#include "Controllers/ConfigurationController.h"
#include "Controllers/LogController.h"
#include "Controllers/ServerListenerController.h"
#include "Controllers/ServerSocketController.h"

int main(int argc, char** argv) {
    std::cout << "+-------------------------------------+" << std::endl;
    std::cout << "| CaveTEK - Multi User Dungeon Engine |" << std::endl;
    std::cout << "|            Version 0.2.0            |" << std::endl;
    std::cout << "|    (c) 2014 - 2022 - CaveFox LLC    |" << std::endl;
    std::cout << "+-------------------------------------+" << std::endl;

    // Load settings from config file passed in as an argument
    // If no argument is passed, load default config file (config.json)
    ConfigurationController configuration_controller = ConfigurationController();
    ConfigurationModel configuration_model;
    if (argc == 2) {
        configuration_model = configuration_controller.getConfiguration(argv[1]);
    } else if (argc == 1) {
        // Load default config file
        configuration_model = configuration_controller.getConfiguration("config.json");
    } else {
        std::cout << "Usage: " << argv[0] << " [config_file]" << std::endl;
        return 1;
    }

    // Create a log controller
    LogController log_controller = LogController(&std::cout, log_controller.string_to_log_level(configuration_model.log_level));
    log_controller.log(log_controller.INFO, "Logger initialized... Starting server...");

    // Print the configuration model
    log_controller.log(log_controller.DEBUG, configuration_model.toString());

    // Initialize a vector of threads to track all the threads we create
    std::vector<std::thread> threads;

    // Initialize the main server socket
    ServerSocketModel server_socket_model = ServerSocketModel();
    ServerSocketController server_socket_controller = ServerSocketController(&server_socket_model, &configuration_model, &log_controller);

    // Start the client socket handler threads
    SessionsModel server_sessions_model = SessionsModel();
    for (int i = 0; i < configuration_model.connection_establishment_handler_thread_count; i++) {
        ServerListenerController server_listener_controller = ServerListenerController(&log_controller, &server_socket_model, &configuration_model, &server_sessions_model);
        threads.push_back(std::thread(&ServerListenerController::start, &server_listener_controller));
    }

    // Start the master game loop threads

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
