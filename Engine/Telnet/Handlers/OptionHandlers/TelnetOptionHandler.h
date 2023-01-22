//
// Created by Travis Canning on 11/11/22.
//

#ifndef CAVEMUD_TELNETOPTIONHANDLER_H
#define CAVEMUD_TELNETOPTIONHANDLER_H

#include "../../../../Utils/Logger/Logger.h"
#include "../../../../Session/Session.h"
#include "../../TelnetConstants.h"
#include "../../../../Utils/Configuration/Configuration.h"

class TelnetOptionHandler {
public:
    virtual void handleWILL(Logger* logger, Configuration* config, Session* session, OptionCode option) = 0;
    virtual void handleWONT(Logger* logger, Configuration* config, Session* session, OptionCode option) = 0;
    virtual void handleDO(Logger* logger, Configuration* config, Session* session, OptionCode option) = 0;
    virtual void handleDONT(Logger* logger, Configuration* config, Session* session, OptionCode option) = 0;
    virtual void handleSB(Logger* logger, Configuration* config, Session* session, OptionCode option, const std::vector<char8_t>& sb_data) = 0;
};

#endif //CAVEMUD_TELNETOPTIONHANDLER_H
