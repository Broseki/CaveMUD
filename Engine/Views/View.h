//
// Created by Travis Canning on 10/31/22.
//

#ifndef CAVEMUD_VIEW_H
#define CAVEMUD_VIEW_H

#include "../Telnet/TelnetSession.h"

class View {
private:
    TelnetSession *telnetSession;
public:
    virtual void render() = 0;
};

#endif //CAVEMUD_VIEW_H
