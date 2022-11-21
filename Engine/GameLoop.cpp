//
// Created by Travis Canning on 10/25/22.
//

#include "GameLoop.h"
#include "Views/View.h"
#include "Views/EchoView.h"
#include "StateMachines/StateMachine.h"
#include "StateMachines/Echo.h"
#include "Telnet/TelnetConstants.h"
#include "Telnet/TelnetController.h"

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
    // If no view is set, set the default view
    if (session->get_view() == nullptr) {
        session->set_view(logger, std::make_shared<EchoView>());
    }

    // Handle any telnet commands that are in the received data stream
    TelnetController::handleCommands(logger, this->configuration, session);

    // Handle input
    if (session->get_view() != nullptr) {
        session->get_view()->handle_input(logger, session);
    }

    // Run State Machines (if any)
    for (const auto& state_machine : session->get_state_machines()) {
        state_machine->step(logger, session);
    }

    // Render
    if (session->get_view() != nullptr) {
        session->get_view()->render(logger, session);
    }
}
