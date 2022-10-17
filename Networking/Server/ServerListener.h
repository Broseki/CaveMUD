//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SERVERLISTENER_H
#define CAVEMUD_SERVERLISTENER_H


#include "../../Utils/Logger/Logger.h"
#include "../../Session/Sessions.h"
#include "ServerSocket.h"

class ServerListener {
public:
    ServerListener(Logger *logger,
                   ServerSocket *server_socket,
                   Configuration *config,
                   Sessions *sessions);
    ~ServerListener();
    void start();
    void stop();

private:
    Logger *logger;
    ServerSocket *server_socket;
    Configuration *config;
    Sessions *sessions;
    bool stopped;

};


#endif //CAVEMUD_SERVERLISTENER_H
