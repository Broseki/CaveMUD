//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SESSIONSCONTROLLER_H
#define CAVEMUD_SESSIONSCONTROLLER_H


#include "../Models/SessionsModel.h"
#include "LogController.h"
#include "../Models/ConfigurationModel.h"

class SessionsController {
public:
    SessionsController(SessionsModel *sessionsModel, ConfigurationModel *config, LogController *log_controller);
    void addSession(std::shared_ptr<SessionModel> session);
    void removeSession(int sessionId);
    uint32_t getNumSessions();

private:
    SessionsModel *sessionsModel;
    ConfigurationModel *config;
    LogController *log_controller;
};


#endif //CAVEMUD_SESSIONSCONTROLLER_H
