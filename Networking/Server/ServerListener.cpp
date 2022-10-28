//
// Created by Travis Canning on 10/16/22.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <netinet/tcp.h>
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
        if (!this->setSocketNonBlocking(client_socket)) {
            this->logger->log(Logger::LogLevel::ERROR,
                                      "ServerListener::start() - Error setting socket to non-blocking");
            this->server_socket->get_socketfd_mutex()->unlock();
            continue;
        }

        // Enable keep-alive on the socket
        if (!this->setSocketKeepAlive(client_socket)) {
            this->logger->log(Logger::LogLevel::ERROR,
                                      "ServerListener::start() - Error setting socket to keep-alive");
            this->server_socket->get_socketfd_mutex()->unlock();
            continue;
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

bool ServerListener::setSocketNonBlocking(int socket) {
    int flags = fcntl(socket, F_GETFL, 0);
    if (flags < 0) {
        this->logger->log(Logger::LogLevel::ERROR,
                          "ServerListener::start() - Error getting socket flags");
        close(socket);
        return false;
    }
    if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) < 0) {
        this->logger->log(Logger::LogLevel::ERROR,
                          "ServerListener::start() - Error setting socket to non-blocking");
        close(socket);
        return false;
    }
    return true;
}

bool ServerListener::setSocketKeepAlive(int socket) {
    int optval = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)) < 0) {
        this->logger->log(Logger::LogLevel::ERROR,
                          "ServerListener::start() - Error setting socket to keep-alive");
        close(socket);
        return false;
    }

    //set the keepalive options
    int rc;
    rc = setsockopt(socket, IPPROTO_TCP, TCP_KEEPCNT, &tcpKeepAliveConfig.keepcnt, sizeof(tcpKeepAliveConfig.keepcnt));
    if (rc != 0) {
        close(socket);
        return false;
    }

    rc = setsockopt(socket, IPPROTO_TCP, TCP_KEEPALIVE, &tcpKeepAliveConfig.keepidle, sizeof(tcpKeepAliveConfig.keepidle));
    if (rc != 0) {
        close(socket);
        return false;
    }

    rc = setsockopt(socket, IPPROTO_TCP, TCP_KEEPINTVL, &tcpKeepAliveConfig.keepintvl, sizeof(tcpKeepAliveConfig.keepintvl));
    if (rc != 0) {
        close(socket);
        return false;
    }

    return true;
}
