//
// Created by Travis Canning on 11/15/22.
//

#include "CommandRouter.h"
#include "AreYouThere.h"
#include "InterruptProcess.h"

void CommandRouter::routeCommand(Logger *logger, Configuration *config, Session* session,
                                 CommandCode command) {
    switch (command) {
        case SE:
            break;
        case NOP:
            break;
        case DATAMARK:
            break;
        case BREAK:
            break;
        case INTERRUPT_PROCESS:
        {
            InterruptProcess interruptProcess;
            interruptProcess.handleCommand(logger, config, session);
        }
            break;
        case ABORT_OUTPUT:
            break;
        case ARE_YOU_THERE:
        {
            AreYouThere handler;
            handler.handleCommand(logger, config, session);
        }
            break;
        case ERASE_CHARACTER:
            break;
        case ERASE_LINE:
            break;
        case GO_AHEAD:
            break;
        case SB:
            break;
        case WILL:
            break;
        case WONT:
            break;
        case DO:
            break;
        case DONT:
            break;
        default:
            break;
    }
}
