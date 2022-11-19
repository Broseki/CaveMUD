//
// Created by Travis Canning on 11/15/22.
//

#ifndef CAVEMUD_COMMANDROUTER_H
#define CAVEMUD_COMMANDROUTER_H


#include "../../TelnetConstants.h"
#include "../../../../Session/Session.h"
#include "../../../../Utils/Configuration/Configuration.h"
#include "TelnetCommandHandler.h"

class CommandRouter {
private:
    std::map<unsigned char, std::shared_ptr<TelnetCommandHandler>> commandHandlers = {};

public:
    static void routeCommand(Logger* logger, Configuration* config, std::shared_ptr<Session> session, CommandCode command);
};


#endif //CAVEMUD_COMMANDROUTER_H
