//
// Created by Travis Canning on 10/16/22.
//

#include "SessionsController.h"
#include <mutex>

SessionsController::SessionsController(SessionsModel *sessionsModel, ConfigurationModel *config, LogController *log_controller) {
    this->sessionsModel = sessionsModel;
    this->config = config;
    this->log_controller = log_controller;
}

void SessionsController::addSession(std::shared_ptr<SessionModel> session) {
    // Lock the sessions mutex safely (RAII)
    const std::lock_guard<std::mutex> lock(sessionsModel->sessions_mutex);

    // If the server is full throw an exception
    if (getNumSessions() >= config->max_players) {
        throw std::runtime_error("Server is full");
    }

    // Add the session to the sessions map
    sessionsModel->sessions[session->socketfd] = session;
}

void SessionsController::removeSession(int sessionId) {
    // Lock the sessions mutex safely (RAII)
    const std::lock_guard<std::mutex> lock(sessionsModel->sessions_mutex);

    // Remove the session from the sessions map
    sessionsModel->sessions.erase(sessionId);
}

uint32_t SessionsController::getNumSessions() {
    // Return the number of sessions
    return sessionsModel->sessions.size();
}
