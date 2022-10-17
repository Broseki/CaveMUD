//
// Created by Travis Canning on 10/16/22.
//

#include "Sessions.h"
#include <mutex>

Sessions::Sessions(Configuration *config, Logger *logger) {
    this->config = config;
    this->logger = logger;
}

void Sessions::addSession(std::shared_ptr<Session> session) {
    // Lock the sessions mutex safely (RAII)
    const std::lock_guard<std::mutex> lock(this->sessions_mutex);

    // If the server is full throw an exception
    if (getNumSessions() >= config->max_players) {
        throw std::runtime_error("Server is full");
    }

    // Add the session to the sessions map
    sessions[session->get_socketfd()] = session;
}

void Sessions::removeSession(int sessionId) {
    // Lock the sessions mutex safely (RAII)
    const std::lock_guard<std::mutex> lock(this->sessions_mutex);

    // Remove the session from the sessions map
    sessions.erase(sessionId);
}

uint32_t Sessions::getNumSessions() {
    // Return the number of sessions
    return sessions.size();
}
