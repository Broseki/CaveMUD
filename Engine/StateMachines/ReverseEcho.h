//
// Created by Travis Canning on 11/20/22.
//

#ifndef CAVEMUD_REVERSEECHO_H
#define CAVEMUD_REVERSEECHO_H


#include "StateMachine.h"

#define ECHO_IN_VAR "echo_in"
#define ECHO_OUT_VAR "echo_out"
#define ECHO_TYPE_VAR "echo_type"

class ReverseEcho: public StateMachine {
public:
    ReverseEcho(): StateMachine("ReverseEcho") {}
    void step(Logger* logger, std::shared_ptr<Session> session) override;
    void reset(Logger* logger, std::shared_ptr<Session> session) override;
    void start(Logger* logger, Session* session) override;
    void stop(Logger* logger, Session* session) override;
};


#endif //CAVEMUD_REVERSEECHO_H
