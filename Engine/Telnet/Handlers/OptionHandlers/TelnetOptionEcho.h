//
// Created by Travis Canning on 1/22/23.
//

#ifndef CAVEMUD_TELNETOPTIONECHO_H
#define CAVEMUD_TELNETOPTIONECHO_H


#include "TelnetOptionHandler.h"

class TelnetOptionEcho: public TelnetOptionHandler {
public:
    void handleWILL(Logger* logger, Configuration* config, Session* session, OptionCode option) override;
    void handleWONT(Logger* logger, Configuration* config, Session* session, OptionCode option) override;
    void handleDO(Logger* logger, Configuration* config, Session* session, OptionCode option) override;
    void handleDONT(Logger* logger, Configuration* config, Session* session, OptionCode option) override;
    void handleSB(Logger* logger, Configuration* config, Session* session, OptionCode option, const std::vector<char8_t>& sb_data) override;
};


#endif //CAVEMUD_TELNETOPTIONECHO_H
