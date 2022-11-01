//
// Created by Travis Canning on 10/31/22.
//

#ifndef CAVEMUD_STATEMACHINE_H
#define CAVEMUD_STATEMACHINE_H

#include "../../Session/Session.h"

// Pre-declare due to circular dependency circular dependency
class Session;

class StateMachine {
public:
    static void step(std::shared_ptr<Session> session);
    static void reset(std::shared_ptr<Session> session);
};

#endif //CAVEMUD_STATEMACHINE_H
