//
// Created by Travis Canning on 10/31/22.
//

#ifndef CAVEMUD_VIEW_H
#define CAVEMUD_VIEW_H

#include "../../Session/Session.h"
#include "../../Utils/Logger/Logger.h"

class Session;

class View {
private:

public:
    virtual void handle_input(Logger* logger, Session* session) = 0;
    virtual void render(Logger* logger, Session* session) = 0;
    virtual void start(Logger* logger, Session* session) = 0;
    virtual void stop(Logger* logger, Session* session) = 0;

protected:
    // Common UI functions
    void set_line_mode(Logger* logger, Session* session);
    bool get_line_mode(Logger* logger, Session* session);
    void set_char_mode(Logger* logger, Session* session);
    bool get_char_mode(Logger* logger, Session* session);
};

#endif //CAVEMUD_VIEW_H
