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

void SessionHandler::rx(const std::shared_ptr<Session>& session) {
    // Receive data from the session
    std::vector<char8_t> input_buffer(configuration->socket_buffer_size);
    int result = recv(session->get_socketfd(), input_buffer.data(), input_buffer.size(), 0);

    if (result == 0) {
        // The client has disconnected
        logger->log(logger->DEBUG, "Client disconnected");
        sessions->removeSession(session->get_socketfd());
    } else if (result < 0) {
        // An error occurred
        logger->log(logger->ERROR, "Error receiving data from client");
        sessions->removeSession(session->get_socketfd());
    } else {
        // Set the input buffer
        session->set_input_buffer(input_buffer);
    }
}

void SessionHandler::tx(const std::shared_ptr<Session>& session) {
    // Send data to the session
    std::vector<char8_t> output_buffer = session->get_output_buffer();
    int result = send(session->get_socketfd(), output_buffer.data(), output_buffer.size(), 0);

    if (result < 0) {
        // An error occurred
        logger->log(logger->ERROR, "Error sending data to client");
        sessions->removeSession(session->get_socketfd());
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

        logger->log(logger->DEBUG, "SessionHandler " + std::to_string(thread_id) + " is running");

        // Get the sessions that we are responsible for
        const std::vector<std::shared_ptr<Session>> my_sessions = this->sessions->getSessions(thread_id, configuration->player_session_socket_handler_thread_count);

        logger->log(logger->DEBUG, "Session handler thread " + std::to_string(thread_id) + " handling " + std::to_string(my_sessions.size()) + " sessions");

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
