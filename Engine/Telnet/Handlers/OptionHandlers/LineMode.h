//
// Created by Travis Canning on 1/22/23.
//

#ifndef CAVEMUD_LINEMODE_H
#define CAVEMUD_LINEMODE_H


#include "TelnetOptionHandler.h"

class LineMode: public TelnetOptionHandler {

public:
    void handleWILL(Logger* logger, Configuration* config, Session* session, OptionCode option) override;
    void handleWONT(Logger* logger, Configuration* config, Session* session, OptionCode option) override;
    void handleDO(Logger* logger, Configuration* config, Session* session, OptionCode option) override;
    void handleDONT(Logger* logger, Configuration* config, Session* session, OptionCode option) override;
    void handleSB(Logger* logger, Configuration* config, Session* session, OptionCode option, const std::vector<char8_t>& sb_data) override;
};


#endif //CAVEMUD_LINEMODE_H
