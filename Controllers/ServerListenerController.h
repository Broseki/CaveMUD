//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SERVERLISTENERCONTROLLER_H
#define CAVEMUD_SERVERLISTENERCONTROLLER_H


#include "LogController.h"
#include "../Models/ConfigurationModel.h"
#include "../Models/SessionModel.h"
#include "../Models/ServerSocketModel.h"
#include "../Models/SessionsModel.h"
#include "SessionsController.h"

class ServerListenerController {
public:
    ServerListenerController(LogController *log_controller,
                             ServerSocketModel *server_socket_model,
                             ConfigurationModel *configuration_model,
                             SessionsModel *sessions);
    ~ServerListenerController();
    void start();
    void stop();

private:
    LogController *log_controller;
    ServerSocketModel *server_socket_model;
    ConfigurationModel *configuration_model;
    SessionsModel *sessions;
    SessionsController *sessions_controller;
    bool stopped;

};


#endif //CAVEMUD_SERVERLISTENERCONTROLLER_H
