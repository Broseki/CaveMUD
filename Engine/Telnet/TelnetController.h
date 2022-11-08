//
// Created by Travis Canning on 11/7/22.
//

#ifndef CAVEMUD_TELNETCONTROLLER_H
#define CAVEMUD_TELNETCONTROLLER_H


#include "../../Utils/Logger/Logger.h"
#include "../../Session/Session.h"
#include "TelnetConstants.h"

class TelnetController {
private:
    /**
     * Handles individual commands, and returns the number of bytes consumed starting from the index
     */
    static uint32_t handleCommand(Logger* logger, const std::shared_ptr<Session>& session, const std::vector<char8_t>& input_buffer, uint32_t index);
public:
    static void handleCommands(Logger* logger, std::shared_ptr<Session> session);
    static void sendCommand(Logger* logger, const std::shared_ptr<Session>&, CommandCode command);
    static void sendCommand(Logger* logger, const std::shared_ptr<Session>&, CommandCode command, OptionCode option);
    static void sendCommand(Logger* logger, const std::shared_ptr<Session>&, CommandCode command, OptionCode option, const std::vector<char8_t>& extra_data);
};


#endif //CAVEMUD_TELNETCONTROLLER_H
