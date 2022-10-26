//
// Created by Travis Canning on 10/26/22.
//

#ifndef CAVEMUD_SESSIONHANDLER_H
#define CAVEMUD_SESSIONHANDLER_H

#include "../Engine/MasterClock.h"
#include "Sessions.h"
#include "../Utils/Logger/Logger.h"
#include "Session.h"
#include "../Utils/Configuration/Configuration.h"

class SessionHandler {

private:
    Logger *logger;
    Configuration *configuration;
    MasterClock *master_clock;
    Sessions *sessions;
    bool stopped;
    uint32_t thread_id;

    void rx(const std::shared_ptr<Session>& session);
    void tx(const std::shared_ptr<Session>& session);


public:
    SessionHandler(Logger *logger, Configuration *configuration, MasterClock *master_clock, Sessions *sessions, uint32_t thread_id);

    void start();
    void stop();
};


#endif //CAVEMUD_SESSIONHANDLER_H
