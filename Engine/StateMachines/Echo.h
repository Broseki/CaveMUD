//
// Created by Travis Canning on 11/1/22.
//

#ifndef CAVEMUD_ECHO_H
#define CAVEMUD_ECHO_H

#include "StateMachine.h"

#define ECHO_IN_VAR "echo_in"
#define ECHO_OUT_VAR "echo_out"

class Echo: public StateMachine {
public:
    static void step(std::shared_ptr<Session> session);
    static void reset(std::shared_ptr<Session> session);
};


#endif //CAVEMUD_ECHO_H
