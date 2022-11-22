//
// Created by Travis Canning on 11/15/22.
//

#include "OptionRouter.h"


void OptionRouter::routeOption(Logger *logger, Configuration *config, std::shared_ptr<Session> session, CommandCode command,
                          OptionCode option, const std::vector<char8_t> &sb_data) {
    logger->log(Logger::DEBUG, "Routing option: " + std::to_string(option) + " with command: " + std::to_string(command));
    OptionRouter router;
    TelnetOptionHandler *handler = router.optionHandlers.at(option).get();
    if (handler == nullptr) {
        logger->log(Logger::ERROR, "No handler for option " + option_code_string_map.at(option));
        return;
    }
    switch (command) {
        case CommandCode::WILL:
            handler->handleWILL(logger, config, session, option);
            break;
        case CommandCode::WONT:
            handler->handleWONT(logger, config, session, option);
            break;
        case CommandCode::DO:
            handler->handleDO(logger, config, session, option);
            break;
        case CommandCode::DONT:
            handler->handleDONT(logger, config, session, option);
            break;
        case CommandCode::SB:
            handler->handleSB(logger, config, session, option, sb_data);
            break;
        default:
            logger->log(Logger::WARNING, "Unknown command code: " + command_code_string_map.at(command) + " for option " + option_code_string_map.at(option));
            break;
    }
}
