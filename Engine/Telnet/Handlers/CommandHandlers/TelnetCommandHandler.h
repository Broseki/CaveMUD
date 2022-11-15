//
// Created by Travis Canning on 11/15/22.
//

#ifndef CAVEMUD_TELNETCOMMANDHANDLER_H
#define CAVEMUD_TELNETCOMMANDHANDLER_H

#include "../../../../Utils/Logger/Logger.h"
#include "../../../../Session/Session.h"
#include "../../TelnetConstants.h"
#include "../../../../Utils/Configuration/Configuration.h"

class TelnetCommandHandler {
public:
    virtual void handleCommand(Logger* logger, Configuration* config, std::shared_ptr<Session> session) = 0;
};


#endif //CAVEMUD_TELNETCOMMANDHANDLER_H
