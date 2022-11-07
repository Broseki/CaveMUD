//
// Created by Travis Canning on 11/1/22.
//

#include "Echo.h"

void Echo::step(Logger* logger, std::shared_ptr<Session> session) {
    boost::any echo_in_var = session->get_kv(ECHO_IN_VAR);
    if (!echo_in_var.empty()) {
        std::string input = boost::any_cast<std::string>(session->get_kv(ECHO_IN_VAR));
        if(input.size() > 0) {
            session->set_kv(ECHO_OUT_VAR, input);
        } else {
            session->remove_kv(ECHO_OUT_VAR);
        }
    }
}

void Echo::reset(Logger* logger, std::shared_ptr<Session> session) {
    session->remove_kv(ECHO_IN_VAR);
    session->remove_kv(ECHO_OUT_VAR);
}
