//
// Created by Travis Canning on 11/1/22.
//

#ifndef CAVEMUD_ECHO_H
#define CAVEMUD_ECHO_H

#include "StateMachine.h"

#define MACHINE_NAME "Echo"
#define ECHO_IN_VAR "echo_in"
#define ECHO_OUT_VAR "echo_out"

class Echo: public StateMachine {
public:
    Echo(): StateMachine(MACHINE_NAME) {}
    void step(Logger* logger, std::shared_ptr<Session> session) override;
    void reset(Logger* logger, std::shared_ptr<Session> session) override;
};


#endif //CAVEMUD_ECHO_H
