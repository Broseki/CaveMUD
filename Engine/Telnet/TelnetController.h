//
// Created by Travis Canning on 11/7/22.
//

#ifndef CAVEMUD_TELNETCONTROLLER_H
#define CAVEMUD_TELNETCONTROLLER_H


#include "../../Utils/Logger/Logger.h"
#include "../../Session/Session.h"
#include "TelnetConstants.h"
#include "../../Utils/Configuration/Configuration.h"

class TelnetController {
private:
    /**
     * Handles individual commands, and returns the number of bytes consumed starting from the index
     */
    static uint32_t handleCommand(Logger* logger, Configuration* config, Session* session, const std::vector<char8_t>& input_buffer, uint32_t index);
public:
    static void handleCommands(Logger* logger, Configuration* config, Session* session);
    static std::vector<char8_t> constructCommand(CommandCode command);
    static std::vector<char8_t> constructCommand(CommandCode command, OptionCode option);
    static std::vector<char8_t> constructCommand(CommandCode command, OptionCode option, const std::vector<char8_t>& extra_data);

    /**
     * Adds to the command append buffer for a user session. These will be sent at the end of the next output buffer
     */
    static void addToCommandAppendBuffer(Logger* logger, Session* session, std::vector<char8_t> bytes);

    /**
     * Adds to the command prepend buffer for a user session. These will be sent at the beginning of the next output buffer
     */
    static void addToCommandPrependBuffer(Logger* logger, Session* session, std::vector<char8_t> bytes);
};


#endif //CAVEMUD_TELNETCONTROLLER_H
