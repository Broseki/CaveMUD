#include <iostream>
#include "Models/ConfigurationModel.h"
#include "Controllers/ConfigurationController.h"
#include "Controllers/LogController.h"

int main(int argc, char** argv) {
    std::cout << "+-------------------------------------+" << std::endl;
    std::cout << "| CaveTEK - Multi User Dungeon Engine |" << std::endl;
    std::cout << "|            Version 0.2.0            |" << std::endl;
    std::cout << "|    (c) 2014 - 2022 - CaveFox LLC    |" << std::endl;
    std::cout << "+-------------------------------------+" << std::endl;

    // Load settings from config file passed in as an argument
    // If no argument is passed, load default config file (config.json)
    ConfigurationController configuration_controller = ConfigurationController();
    std::shared_ptr<ConfigurationModel> configuration_model;
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
    LogController log_controller = LogController(&std::cout, log_controller.string_to_log_level(configuration_model->log_level));
    log_controller.log(log_controller.INFO, "Logger initialized... Starting server...");

    // Print the configuration model
    log_controller.log(log_controller.DEBUG, configuration_model->toString());

    // Start the main server listener threads
    log_controller.log(log_controller.INFO, "Starting server listener threads...");


    // Start the client socket handler threads

    // Start the master game loop threads

    // Join threads

    return 0;
}
