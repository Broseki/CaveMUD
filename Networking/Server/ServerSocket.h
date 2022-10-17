//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SERVERSOCKET_H
#define CAVEMUD_SERVERSOCKET_H

#include "../../Utils/Configuration/Configuration.h"
#include "../../Utils/Logger/Logger.h"

class ServerSocket {
public:
    ServerSocket(Configuration *config, Logger *logger);
    ~ServerSocket();

    int get_socketfd();
    std::mutex *get_socketfd_mutex();

private:
    Logger *logger;
    int socketfd;
    std::mutex socket_mutex;
};


#endif //CAVEMUD_SERVERSOCKET_H
