//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SERVERSOCKETCONTROLLER_H
#define CAVEMUD_SERVERSOCKETCONTROLLER_H

#include "../Models/ServerSocketModel.h"
#include "../Models/ConfigurationModel.h"
#include "LogController.h"

class ServerSocketController {
public:
    ServerSocketController(ServerSocketModel* serverSocketModel, ConfigurationModel *config, LogController *log_controller);
    ~ServerSocketController();

    ServerSocketModel *get_server_socket_model();

private:
    ServerSocketModel *server_socket_model;
    LogController *log_controller;
};


#endif //CAVEMUD_SERVERSOCKETCONTROLLER_H
