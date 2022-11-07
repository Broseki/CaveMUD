//
// Created by Travis Canning on 11/2/22.
//

#include "EchoView.h"
#include "../StateMachines/Echo.h"

void EchoView::render(Logger* logger, std::shared_ptr<Session> session) {
    boost::any echo_out_var = session->get_kv(ECHO_OUT_VAR);
    if (!echo_out_var.empty()) {
        std::string output = boost::any_cast<std::string>(session->get_kv(ECHO_OUT_VAR));
        session->set_output_buffer(std::vector<char8_t>(output.begin(), output.end()));
    }
}

void EchoView::handle_input(Logger* logger, std::shared_ptr<Session> session) {
    std::vector<char8_t> input_buffer = session->get_input_buffer();
    std::string input(input_buffer.begin(), input_buffer.end());
    session->set_kv(ECHO_IN_VAR, input);
    session->clear_input_buffer();
}
