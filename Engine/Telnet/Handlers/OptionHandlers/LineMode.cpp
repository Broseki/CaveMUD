//
// Created by Travis Canning on 1/22/23.
//

#include "LineMode.h"
#include "../../../../Session/KV_Keys.h"

void LineMode::handleWILL(Logger *logger, Configuration *config, Session *session, OptionCode option) {
    // TODO
}

void LineMode::handleWONT(Logger *logger, Configuration *config, Session *session, OptionCode option) {
    // TODO
}

void LineMode::handleDO(Logger *logger, Configuration *config, Session *session, OptionCode option) {
    // Ignore, we are the server
    return;
}

void LineMode::handleDONT(Logger *logger, Configuration *config, Session *session, OptionCode option) {
    // TODO
}

void LineMode::handleSB(Logger *logger, Configuration *config, Session *session, OptionCode option,
                        const std::vector<char8_t> &sb_data) {
    // TODO
    return;
}
