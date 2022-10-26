//
// Created by Travis Canning on 10/16/22.
//

#include "Sessions.h"
#include <mutex>
#include <unistd.h>

Sessions::Sessions(Configuration *config, Logger *logger) {
    this->config = config;
    this->logger = logger;
}

Sessions::~Sessions() {
    logger->log(logger->INFO, "Destroying Sessions object");
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

void Sessions::removeSession(int sessionId, bool closeSocket) {
    // Lock the sessions mutex safely (RAII)
    const std::lock_guard<std::mutex> lock(this->sessions_mutex);

    // Close the socket if requested
    if (closeSocket) {
        close(sessions[sessionId]->get_socketfd());
    }

    // Remove the session from the sessions map
    sessions.erase(sessionId);
}

uint32_t Sessions::getNumSessions() {
    // Return the number of sessions
    return sessions.size();
}

std::vector<std::shared_ptr<Session>> Sessions::getSessions(uint32_t offset, uint32_t step) {
    // Lock the sessions mutex safely (RAII)
    const std::lock_guard<std::mutex> lock(this->sessions_mutex);

    // Create a vector of sessions
    std::vector<std::shared_ptr<Session>> sessions_to_return;

    // Iterate through sessions on the offset and add them to the vector
    for (auto it = sessions.begin(); it != sessions.end(); it++) {
        if (it->first % step == offset) {
            sessions_to_return.push_back(it->second);
        }
    }

    // Return the vector of sessions
    return sessions_to_return;
}