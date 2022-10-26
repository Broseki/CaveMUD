//
// Created by Travis Canning on 10/25/22.
//

#ifndef CAVEMUD_GAMELOOP_H
#define CAVEMUD_GAMELOOP_H


#include "../Utils/Logger/Logger.h"
#include "../Utils/Configuration/Configuration.h"
#include "MasterClock.h"
#include "../Session/Sessions.h"

class GameLoop {
private:
    Logger *logger;
    Configuration *configuration;
    MasterClock *master_clock;
    Sessions *sessions;
    bool stopped;
    uint32_t thread_id;

    void handleSession(const std::shared_ptr<Session>& session);

public:
    GameLoop(Logger *logger, Configuration *configuration, MasterClock *master_clock, Sessions *sessions, uint32_t thread_id);
    ~GameLoop();

    void start();
    void stop();
};


#endif //CAVEMUD_GAMELOOP_H
