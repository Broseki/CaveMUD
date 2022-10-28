//
// Created by Travis Canning on 10/26/22.
//

#include <sys/socket.h>
#include "SessionHandler.h"

SessionHandler::SessionHandler(Logger *logger, Configuration *configuration, MasterClock *master_clock, Sessions *sessions, uint32_t thread_id) {
    this->logger = logger;
    this->configuration = configuration;
    this->master_clock = master_clock;
    this->sessions = sessions;
    this->thread_id = thread_id;
    this->stopped = false;
}

SessionHandler::~SessionHandler() {
    logger->log(logger->INFO, "Destroying SessionHandler ID " + std::to_string(this->thread_id));
    stop();
}

void SessionHandler::rx(const std::shared_ptr<Session>& session) {
    // Receive data from the session
    std::vector<char8_t> temp_input_buffer(configuration->socket_buffer_size);
    int result = recv(session->get_socketfd(), temp_input_buffer.data(), temp_input_buffer.size(), 0);

    if (result == 0) {
        // The client has disconnected
        logger->log(logger->INFO, "Client disconnected [ " + std::to_string(session->get_socketfd()) + " ]");
        sessions->removeSession(session->get_socketfd(), true);
    } else if (result < 0 && errno != EWOULDBLOCK) {
        // An error occurred
        logger->log(logger->INFO, "Error receiving data from client [ " + std::to_string(session->get_socketfd()) + " ]");
        sessions->removeSession(session->get_socketfd(), false);
    } else if (result > 0) {
        std::vector<char8_t> input_buffer;
        while (result > 0) {
            // Append the received data to the input buffer
            input_buffer.insert(input_buffer.end(), temp_input_buffer.begin(), temp_input_buffer.begin() + result);

            // Receive more data
            result = recv(session->get_socketfd(), temp_input_buffer.data(), temp_input_buffer.size(), 0);
        }
        logger->log(logger->DEBUG, "[SessionHandler # " + std::to_string(thread_id) + "] Received: " + std::string(input_buffer.begin(), input_buffer.begin() + input_buffer.size()));
        session->set_input_buffer(input_buffer);
    }
}

void SessionHandler::tx(const std::shared_ptr<Session>& session) {
    // Send data to the session
    std::vector<char8_t> output_buffer = session->get_output_buffer();
    int result = send(session->get_socketfd(), output_buffer.data(), output_buffer.size(), 0);

    if (result < 0) {
        // An error occurred
        logger->log(logger->INFO, "Error sending data to client [ " + std::to_string(session->get_socketfd()) + " ]");
        sessions->removeSession(session->get_socketfd(), false);
    } else {
        // Clear the output buffer
        session->clear_output_buffer();
    }
}

void SessionHandler::start() {
    while (!stopped) {
        // Notify the master clock that we are ready and wait for ready signal
        master_clock->readyCallback();
        master_clock->waitOnReadyMutex();

        // Get the sessions that we are responsible for
        const std::vector<std::shared_ptr<Session>> my_sessions = this->sessions->getSessions(thread_id, configuration->player_session_socket_handler_thread_count);

        // Receive and transmit data for each session
        for (const auto& session : my_sessions) {
            rx(session);
            tx(session);
        }

        // Notify the master clock that we are done
        master_clock->doneCallback();
        master_clock->waitOnSessionControllerModeMutex();
    }
}

void SessionHandler::stop() {
    stopped = true;
}
