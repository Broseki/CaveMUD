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

        // Handle each of the sessions that this thread is responsible for
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
    logger->log(logger->DEBUG, "Game loop # " + std::to_string(thread_id) + " handling session # " + std::to_string(session->get_socketfd()));

    // Run the state machines
}
