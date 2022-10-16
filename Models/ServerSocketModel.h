//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SERVERSOCKETMODEL_H
#define CAVEMUD_SERVERSOCKETMODEL_H

#include <mutex>

class ServerSocketModel {
public:
    int socketfd;
    std::mutex socket_mutex;
};


#endif //CAVEMUD_SERVERSOCKETMODEL_H
