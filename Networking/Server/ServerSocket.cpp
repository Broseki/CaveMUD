//
// Created by Travis Canning on 10/16/22.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ServerSocket.h"

ServerSocket::ServerSocket(Configuration *config, Logger *logger) {
    this->logger = logger;
    // Create a socket
    logger->log(Logger::LogLevel::DEBUG, "ServerSocket::ServerSocket() - Creating socket");
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd < 0) {
        this->logger->log(logger->FATAL, "Error opening socket");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the port specified in the configuration
    logger->log(Logger::LogLevel::DEBUG, "ServerSocket::ServerSocket() - Binding socket to port " + std::to_string(config->game_port));
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(config->game_port);
    if (bind(this->socketfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        this->logger->log(logger->FATAL, "Error binding socket to port " + std::to_string(config->game_port));
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    logger->log(Logger::LogLevel::DEBUG, "ServerSocket::ServerSocket() - Listening for connections");
    listen(this->socketfd, config->connection_queue_size);
}

ServerSocket::~ServerSocket() {
    logger->log(logger->INFO, "Destroying ServerSocket");
    this->socket_mutex.lock();
    close(this->socketfd);
    this->socketfd = -1;
    this->socket_mutex.unlock();
}

int ServerSocket::get_socketfd() {
    return this->socketfd;
}

std::mutex *ServerSocket::get_socketfd_mutex() {
    return &this->socket_mutex;
}
