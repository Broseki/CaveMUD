//
// Created by Travis Canning on 11/15/22.
//

#ifndef CAVEMUD_OPTIONROUTER_H
#define CAVEMUD_OPTIONROUTER_H


#include <map>
#include "TelnetOptionHandler.h"

class OptionRouter {
private:
    std::map<unsigned char, std::shared_ptr<TelnetOptionHandler>> optionHandlers = {};

public:
    static void routeOption(Logger* logger, Configuration* config, std::shared_ptr<Session> session, CommandCode command, OptionCode option, const std::vector<char8_t>& sb_data);
};


#endif //CAVEMUD_OPTIONROUTER_H
