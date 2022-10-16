//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SESSIONSMODEL_H
#define CAVEMUD_SESSIONSMODEL_H

#include <unordered_map>
#include <mutex>
#include "SessionModel.h"

class SessionsModel {
public:
    std::unordered_map<int, std::shared_ptr<SessionModel>> sessions;
    std::mutex sessions_mutex;
};

#endif //CAVEMUD_SESSIONSMODEL_H
