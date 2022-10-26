//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SESSIONS_H
#define CAVEMUD_SESSIONS_H

#include <unordered_map>

#include "../Utils/Logger/Logger.h"
#include "../Utils/Configuration/Configuration.h"
#include "Session.h"

class Sessions {
public:
    Sessions(Configuration *config, Logger *logger);
    ~Sessions();
    void addSession(std::shared_ptr<Session> session);
    void removeSession(int sessionId);
    uint32_t getNumSessions();
    std::vector<std::shared_ptr<Session>> getSessions(uint32_t offset, uint32_t step);

private:
    Configuration *config;
    Logger *logger;
    std::unordered_map<int, std::shared_ptr<Session>> sessions;
    std::mutex sessions_mutex;
};


#endif //CAVEMUD_SESSIONS_H
