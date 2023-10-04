//
// Created by Travis Canning on 11/2/22.
//

#include "EchoView.h"
#include "../StateMachines/Echo.h"
#include "../../Session/KV_Keys.h"
#include "../StateMachines/ReverseEcho.h"
#include "echo.pb.h"

#define ECHO_TYPE_VAR "echo_type"

void EchoView::render(Logger* logger, Session* session) {
    boost::any echo_out_var = session->get_kv(ECHO_OUT_VAR);
    if (!echo_out_var.empty()) {
        std::string output = boost::any_cast<std::string>(session->get_kv(ECHO_OUT_VAR));
        // Encode the output string into a protobuf message
        CaveMUDProto::Echo echo;
        echo.set_message_text(output);
        // Serialize the protobuf message into a char8_t array and put it in the output buffer
        std::vector<char8_t> output_buffer(echo.ByteSizeLong());
        echo.SerializeToArray(output_buffer.data(), output_buffer.size());
        session->set_output_buffer(output_buffer);
    }

    // Handle the are you there flag
    if (!session->get_kv(SESSION_KV_AYT_FLAG).empty() && boost::any_cast<bool>(session->get_kv(SESSION_KV_AYT_FLAG))) {
        session->remove_kv(SESSION_KV_AYT_FLAG);
        // Append "AYT" to the output buffer
        std::vector<char8_t> output = session->get_output_buffer();
        output.insert(output.end(), {'\n', 'A', 'Y', 'T', '\n'});
        session->set_output_buffer(output);

        // Flip echo mode (just for fun)
        if (!session->get_kv(ECHO_TYPE_VAR).empty() && boost::any_cast<std::string>(session->get_kv(ECHO_TYPE_VAR)) == "Reverse") {
            session->remove_state_machine(logger, "ReverseEcho");
            session->add_state_machine(logger, std::make_shared<Echo>());
        } else {
            session->remove_state_machine(logger, "Echo");
            session->add_state_machine(logger, std::make_shared<ReverseEcho>());
        }
    }

    // Handle the interrupt flag
    if (!session->get_kv(SESSION_KV_INTERRUPT_FLAG).empty() && boost::any_cast<bool>(session->get_kv(SESSION_KV_INTERRUPT_FLAG))) {
        session->remove_kv(SESSION_KV_INTERRUPT_FLAG);
    }
}

void EchoView::handle_input(Logger* logger, Session* session) {
    std::vector<char8_t> input_buffer = session->get_input_buffer();
    // The buffer will hold a protobuf message, decode the string and put it in input
    CaveMUDProto::Echo echo;
    if (!echo.ParseFromArray(input_buffer.data(), input_buffer.size())) {
        logger->log(Logger::ERROR, "Failed to parse Echo message");
        return;
    }
    // Store the value of message_text in the input variable
    std::string input = echo.message_text();
    session->set_kv(ECHO_IN_VAR, input);
    session->clear_input_buffer();
}

void EchoView::start(Logger *logger, Session* session) {
    logger->log(logger->DEBUG, "Starting EchoView");

    // Enable the echo state machine
    session->add_state_machine(logger, std::make_shared<Echo>());
}

void EchoView::stop(Logger *logger, Session* session) {
    logger->log(logger->DEBUG, "Stopping EchoView");

    // Disable the echo state machine
    session->remove_state_machine(logger, "Echo");

    // Disable the reverse echo state machine
    session->remove_state_machine(logger, "ReverseEcho");
}