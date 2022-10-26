//
// Created by Travis Canning on 10/16/22.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include "ServerListener.h"

#define SERVER_FULL_MESSAGE "Server is full. Please try again later."

ServerListener::ServerListener(Logger *logger,
                               ServerSocket *server_socket,
                               Configuration *config,
                               Sessions *sessions) {
    this->logger = logger;
    this->server_socket = server_socket;
    this->config = config;
    this->sessions = sessions;

    this->stopped = false;
}

ServerListener::~ServerListener() {
    logger->log(logger->INFO, "Destroying ServerListener");
    this->stop();
}

void ServerListener::start() {
    while (!this->stopped) {
        // Lock the socket mutex and accept a new connection
        this->server_socket->get_socketfd_mutex()->lock();
        if (this->server_socket->get_socketfd() < 0) {
            this->logger->log(Logger::LogLevel::FATAL,
                                      "ServerListener::start() - Socket is closed");
            this->stop();
            return;
        }
        struct sockaddr_in address;
        socklen_t address_length = sizeof(address);
        int client_socket = accept(this->server_socket->get_socketfd(), (struct sockaddr *) &address, &address_length);

        // Set the socket to non-blocking
        int flags = fcntl(client_socket, F_GETFL, 0);
        if (flags < 0) {
            this->logger->log(Logger::LogLevel::ERROR,
                                      "ServerListener::start() - Error getting socket flags");
            close(client_socket);
            return;
        }
        if (fcntl(client_socket, F_SETFL, flags | O_NONBLOCK) < 0) {
            this->logger->log(Logger::LogLevel::ERROR,
                                      "ServerListener::start() - Error setting socket to non-blocking");
            close(client_socket);
            return;
        }

        if (client_socket < 0) {
            this->logger->log(Logger::LogLevel::ERROR,
                                      "ServerListener::start() - Error accepting connection");
            this->server_socket->get_socketfd_mutex()->unlock();
            continue;
        }

        // Unlock the socket mutex and handle the session initialization tasks
        this->server_socket->get_socketfd_mutex()->unlock();
        this->logger->log(Logger::LogLevel::INFO,
                                  "ServerListener - Accepted connection from [" +
                                  std::string(inet_ntoa(address.sin_addr)) + "]");

        std::shared_ptr<Session> session = std::make_shared<Session>(client_socket);

        try {
            this->sessions->addSession(session);
        } catch (std::runtime_error &e) {
            this->logger->log(Logger::LogLevel::ERROR,
                                      "ServerListener - " + std::string(e.what()) + " dropping connection from [" +
                                        std::string(inet_ntoa(address.sin_addr)) + "]");
            std::string message = SERVER_FULL_MESSAGE;
            message += "\n";
            send(client_socket, message.c_str(), message.size(), 0);
            close(client_socket);
            continue;
        }

        logger->log(logger->DEBUG, "Setup session, now there are " + std::to_string(this->sessions->getNumSessions()) + " sessions");
    }
}

void ServerListener::stop() {
    this->stopped = true;
}
