//
// Created by Travis Canning on 11/20/22.
//

#ifndef CAVEMUD_INTERRUPTPROCESS_H
#define CAVEMUD_INTERRUPTPROCESS_H


#include "TelnetCommandHandler.h"

class InterruptProcess: public TelnetCommandHandler {
public:
    void handleCommand(Logger* logger, Configuration* config, Session* session) override;
};


#endif //CAVEMUD_INTERRUPTPROCESS_H
