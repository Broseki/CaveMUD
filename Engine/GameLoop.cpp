//
// Created by Travis Canning on 10/25/22.
//

#include "GameLoop.h"
#include "../Session/Sessions.h"

GameLoop::GameLoop(Logger *logger, Configuration *configuration, MasterClock *master_clock, Sessions *sessions, uint32_t thread_id) {
    this->logger = logger;
    this->configuration = configuration;
    this->master_clock = master_clock;
    this->sessions = sessions;
    this->thread_id = thread_id;
    this->stopped = false;
}

GameLoop::~GameLoop() {
    logger->log(logger->INFO, "Destroying GameLoop ID " + std::to_string(this->thread_id));
    stop();
}

void GameLoop::start() {
    while (!stopped) {
        // Notify the master clock that we are ready and wait for ready signal
        master_clock->waitOnEngineModeMutex();
        master_clock->readyCallback();
        master_clock->waitOnReadyMutex();

        // Do game loop stuff (for now just echo back the input)
        std::vector<std::shared_ptr<Session>> my_sessions = sessions->getSessions(thread_id, configuration->game_loop_thread_count);

        for (const auto& session : my_sessions) {
            handleSession(session);
        }

        // Notify the master clock that we are done
        master_clock->doneCallback();
    }
}

void GameLoop::stop() {
    stopped = true;
}

void GameLoop::handleSession(const std::shared_ptr<Session> &session) {
    std::vector<char8_t> buffer = session->get_input_buffer();
    if(buffer.size() > 0) {
        logger->log(logger->INFO, "Received: " + std::string(buffer.begin(), buffer.begin() + buffer.size()));
    }
    session->set_output_buffer(session->get_input_buffer());

    // Clear the input buffer since we are done with it
    session->clear_input_buffer();
}
