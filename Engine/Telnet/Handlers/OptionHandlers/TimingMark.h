//
// Created by Travis Canning on 11/22/22.
//

#ifndef CAVEMUD_TIMINGMARK_H
#define CAVEMUD_TIMINGMARK_H


#include "TelnetOptionHandler.h"

class TimingMark: public TelnetOptionHandler {
public:
    void handleWILL(Logger* logger, Configuration* config, std::shared_ptr<Session> session, OptionCode option) override;
    void handleWONT(Logger* logger, Configuration* config, std::shared_ptr<Session> session, OptionCode option) override;
    void handleDO(Logger* logger, Configuration* config, std::shared_ptr<Session> session, OptionCode option) override;
    void handleDONT(Logger* logger, Configuration* config, std::shared_ptr<Session> session, OptionCode option) override;
    void handleSB(Logger* logger, Configuration* config, std::shared_ptr<Session> session, OptionCode option, const std::vector<char8_t>& sb_data) override;

};


#endif //CAVEMUD_TIMINGMARK_H
