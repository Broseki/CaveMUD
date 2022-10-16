//
// Created by Travis Canning on 10/16/22.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ServerSocketController.h"

ServerSocketController::ServerSocketController(ServerSocketModel* serverSocketModel, ConfigurationModel *config, LogController *log_controller) {
    this->server_socket_model = serverSocketModel;
    this->log_controller = log_controller;
    // Create a socket
    log_controller->log(LogController::LogLevel::DEBUG, "ServerSocketController::ServerSocketController() - Creating socket");
    this->server_socket_model->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_socket_model->socketfd < 0) {
        this->log_controller->log(log_controller->FATAL, "Error opening socket");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the port specified in the configuration
    log_controller->log(LogController::LogLevel::DEBUG, "ServerSocketController::ServerSocketController() - Binding socket to port " + std::to_string(config->game_port));
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config->game_port);
    if (bind(this->server_socket_model->socketfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        this->log_controller->log(log_controller->FATAL, "Error binding socket to port" + std::to_string(config->game_port));
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    log_controller->log(LogController::LogLevel::DEBUG, "ServerSocketController::ServerSocketController() - Listening for connections");
    listen(this->server_socket_model->socketfd, config->connection_queue_size);
}

ServerSocketController::~ServerSocketController() {
    this->server_socket_model->socket_mutex.lock();
    close(this->server_socket_model->socketfd);
    this->server_socket_model->socketfd = -1;
    this->server_socket_model->socket_mutex.unlock();
}

ServerSocketModel *ServerSocketController::get_server_socket_model() {
    return this->server_socket_model;
}
