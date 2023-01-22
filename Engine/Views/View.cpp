//
// Created by Travis Canning on 1/22/23.
//
#include "View.h"
#include "../../Session/KV_Keys.h"
#include "../Telnet/TelnetController.h"

void View::set_line_mode(Logger* logger, Session* session) {
    logger->log(Logger::DEBUG, "View::set_line_mode");
    // TODO
}

void View::set_char_mode(Logger* logger, Session* session) {
    logger->log(Logger::DEBUG, "View::set_char_mode");
    // TODO
}

bool View::get_line_mode(Logger *logger, Session *session) {
    boost::any line_mode = session->get_kv(SESSION_LINE_MODE);
    if (!line_mode.empty()) {
        return boost::any_cast<bool>(line_mode);
    } else {
        return false;
    }
}

bool View::get_char_mode(Logger *logger, Session *session) {
    boost::any line_mode = session->get_kv(SESSION_LINE_MODE);
    if (!line_mode.empty()) {
        return !boost::any_cast<bool>(line_mode);
    } else {
        return false;
    }
}
