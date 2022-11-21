//
// Created by Travis Canning on 11/20/22.
//

#include "ReverseEcho.h"

void ReverseEcho::step(Logger* logger, std::shared_ptr<Session> session) {
    boost::any echo_in_var = session->get_kv(ECHO_IN_VAR);
    if (!echo_in_var.empty()) {
        std::string input = boost::any_cast<std::string>(session->get_kv(ECHO_IN_VAR));
        if(input.size() > 0) {
            // Remove newline and reverse string
            input.pop_back();
            std::reverse(input.begin(), input.end());

            // Add newline back
            input.push_back('\n');
            session->set_kv(ECHO_OUT_VAR, input);
        } else {
            session->remove_kv(ECHO_OUT_VAR);
        }
    }
}

void ReverseEcho::reset(Logger* logger, std::shared_ptr<Session> session) {
    session->remove_kv(ECHO_IN_VAR);
    session->remove_kv(ECHO_OUT_VAR);
}

void ReverseEcho::start(Logger *logger, Session *session) {
    logger->log(logger->DEBUG, "Starting ReverseEcho");

    session->set_kv(ECHO_TYPE_VAR, std::string("Reverse"));
}

void ReverseEcho::stop(Logger *logger, Session *session) {
    logger->log(logger->DEBUG, "Stopping ReverseEcho");

    session->remove_kv(ECHO_TYPE_VAR);
}
