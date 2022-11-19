//
// Created by Travis Canning on 11/19/22.
//

#ifndef CAVEMUD_AREYOUTHERE_H
#define CAVEMUD_AREYOUTHERE_H

#include "TelnetCommandHandler.h"

class AreYouThere: public TelnetCommandHandler {
public:
    void handleCommand(Logger* logger, Configuration* config, std::shared_ptr<Session> session) override;
};


#endif //CAVEMUD_AREYOUTHERE_H
