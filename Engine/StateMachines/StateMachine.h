//
// Created by Travis Canning on 10/31/22.
//

#ifndef CAVEMUD_STATEMACHINE_H
#define CAVEMUD_STATEMACHINE_H

#include "../../Session/Session.h"
#include "../../Utils/Logger/Logger.h"

// Pre-declare due to circular dependency circular dependency
class Session;

class StateMachine {
public:
    virtual void step(Logger* logger, std::shared_ptr<Session> session) = 0;
    virtual void reset(Logger* logger, std::shared_ptr<Session> session) = 0;
};

#endif //CAVEMUD_STATEMACHINE_H
