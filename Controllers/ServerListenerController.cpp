//
// Created by Travis Canning on 10/16/22.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include "ServerListenerController.h"

ServerListenerController::ServerListenerController(LogController *log_controller,
                                                   ServerSocketModel *server_socket_model,
                                                   ConfigurationModel *configuration_model,
                                                   SessionsModel *sessions) {
    log_controller->log(LogController::LogLevel::DEBUG, "ServerListenerController::ServerListenerController()");
    this->log_controller = log_controller;
    this->server_socket_model = server_socket_model;
    this->configuration_model = configuration_model;
    this->sessions = sessions;

    this->stopped = false;
}

ServerListenerController::~ServerListenerController() {
    this->stop();
}

void ServerListenerController::start() {
    while (!this->stopped) {
        // Lock the socket mutex and accept a new connection
        this->server_socket_model->socket_mutex.lock();
        if (this->server_socket_model->socketfd < 0) {
            this->log_controller->log(LogController::LogLevel::FATAL, "ServerListenerController::start() - Socket is closed");
            this->stop();
            return;
        }
        struct sockaddr_in address;
        socklen_t address_length = sizeof(address);
        int client_socket = accept(this->server_socket_model->socketfd, (struct sockaddr *) &address, &address_length);
        if (client_socket < 0) {
            this->log_controller->log(LogController::LogLevel::ERROR, "ServerListenerController::start() - Error accepting connection");
            this->server_socket_model->socket_mutex.unlock();
            continue;
        }

        // Unlock the socket mutex and handle the session initialization tasks
        this->server_socket_model->socket_mutex.unlock();
        this->log_controller->log(LogController::LogLevel::INFO, "ServerListenerController - Accepted connection from [" + std::string(inet_ntoa(address.sin_addr)) + "]");

        std::shared_ptr<SessionModel> session = std::make_shared<SessionModel>();
        session->socketfd = client_socket;

        // Lock the sessions mutex and add the new session
        this->sessions->sessions_mutex.lock();
        this->sessions->sessions.insert(std::pair<int, std::shared_ptr<SessionModel>>(client_socket, session));

        // Unlock the sessions mutex
        this->sessions->sessions_mutex.unlock();
    }
}

void ServerListenerController::stop() {

}
