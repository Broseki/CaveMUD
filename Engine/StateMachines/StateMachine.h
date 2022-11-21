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
private:
    std::string machine_name;
public:
    StateMachine(std::string machine_name) {
        this->machine_name = machine_name;
    }

    virtual void step(Logger* logger, std::shared_ptr<Session> session) = 0;

    virtual void reset(Logger* logger, std::shared_ptr<Session> session) = 0;

    virtual void start(Logger* logger, Session* session) = 0;

    virtual void stop(Logger* logger, Session* session) = 0;

    virtual const std::string get_machine_name() {
        return machine_name;
    }
};

#endif //CAVEMUD_STATEMACHINE_H
