//
// Created by Travis Canning on 10/31/22.
//

#ifndef CAVEMUD_STATEMACHINE_H
#define CAVEMUD_STATEMACHINE_H

#include "../../Session/Session.h"
#include "../../Utils/Logger/Logger.h"

// Pre-declare due to circular dependency
class Session;

class StateMachine {
private:
    const std::string machine_name;
    // Flag to indicate if the machine is meant to have any stop logic
    const bool m_steppable;
public:
    StateMachine(std::string machine_name);

    StateMachine(std::string machine_name, bool steppable);

    virtual void step(Logger* logger, std::shared_ptr<Session> session) = 0;

    virtual void reset(Logger* logger, std::shared_ptr<Session> session) = 0;

    virtual void start(Logger* logger, Session* session) = 0;

    virtual void stop(Logger* logger, Session* session) = 0;

    virtual std::string get_machine_name() {
        return machine_name;
    }

    virtual bool is_steppable() {
        return m_steppable;
    }
};

#endif //CAVEMUD_STATEMACHINE_H
