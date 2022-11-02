//
// Created by Travis Canning on 11/2/22.
//

#ifndef CAVEMUD_ECHOVIEW_H
#define CAVEMUD_ECHOVIEW_H

#include "View.h"

class View;

class EchoView: public View {
public:
    void render(Logger* logger, std::shared_ptr<Session> session) override;
    void handle_input(Logger* logger, std::shared_ptr<Session> session) override;
};


#endif //CAVEMUD_ECHOVIEW_H
