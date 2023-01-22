//
// Created by Travis Canning on 11/22/22.
//

#include "TimingMark.h"
#include "../../TelnetController.h"

void
TimingMark::handleWILL(Logger *logger, Configuration *config, Session* session, OptionCode option) {
    // Do nothing
    return;
}

void
TimingMark::handleWONT(Logger *logger, Configuration *config, Session* session, OptionCode option) {
    // Do nothing
    return;
}

void TimingMark::handleDO(Logger *logger, Configuration *config, Session* session, OptionCode option) {
    // SEND WILL
    std::vector<char8_t> data = TelnetController::constructCommand(CommandCode::WILL, OptionCode::TIMING_MARK);
    TelnetController::addToCommandAppendBuffer(logger, session, data);
}

void
TimingMark::handleDONT(Logger *logger, Configuration *config, Session* session, OptionCode option) {
    // Send WONT
    std::vector<char8_t> data = TelnetController::constructCommand(CommandCode::WONT, OptionCode::TIMING_MARK);
    TelnetController::addToCommandAppendBuffer(logger, session, data);
}

void TimingMark::handleSB(Logger *logger, Configuration *config, Session* session, OptionCode option,
                          const std::vector<char8_t> &sb_data) {
    // Subnegotionation doesn't do anything for this option. Just ignore it.
    return;
}
