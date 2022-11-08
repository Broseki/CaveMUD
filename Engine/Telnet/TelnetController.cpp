//
// Created by Travis Canning on 11/7/22.
//

#include "TelnetController.h"

void TelnetController::handleCommands(Logger *logger, std::shared_ptr<Session> session) {
    std::vector<char8_t> input_buffer = session->get_input_buffer();

    // Loop through the input buffer, and handle each command that we find
    // Remove the command from the input buffer once it's been handled
    uint32_t index = 0;
    while (index < input_buffer.size()) {
        if (input_buffer[index] == IAC) {
            uint32_t bytes_consumed = handleCommand(logger, session, input_buffer, index);
            input_buffer.erase(input_buffer.begin() + index, input_buffer.begin() + index + bytes_consumed);
        } else {
            index++;
        }
    }

}

void TelnetController::sendCommand(Logger *logger, const std::shared_ptr<Session>&, CommandCode command) {

}

void TelnetController::sendCommand(Logger *logger, const std::shared_ptr<Session>&, CommandCode command, OptionCode option) {

}

void TelnetController::sendCommand(Logger *logger, const std::shared_ptr<Session>&, CommandCode command, OptionCode option, const std::vector<char8_t>& extra_data) {

}

uint32_t TelnetController::handleCommand(Logger *logger, const std::shared_ptr<Session>& session, const std::vector<char8_t>& input_buffer,
                                uint32_t index) {
    logger->log(Logger::DEBUG, "Handling command at index " + std::to_string(index));

    // Check if the IAC is followed by another IAC (escaped)
    if (input_buffer.size() >= index + 2 && input_buffer[index + 1] == IAC) {
        logger->log(Logger::DEBUG, "Detected IAC escape, skipping");
        return 1;
    }

    // Handle if the IAC is followed by WILL/WONT/DO/DONT
    if (input_buffer.size() >= index + 2 && (input_buffer[index + 1] == WILL || input_buffer[index + 1] == WONT ||
                                           input_buffer[index + 1] == DO || input_buffer[index + 1] == DONT)) {
        if (input_buffer.size() < index + 3) {
            logger->log(Logger::DEBUG, "Received incomplete command, ignoring");
            return 2;
        }
        CommandCode command = static_cast<CommandCode>(input_buffer[index + 1]);
        OptionCode option = static_cast<OptionCode>(input_buffer[index + 2]);
        logger->log(Logger::DEBUG, "Received command " + command_code_map.at(command) + " for option " + option_code_map.at(option));
        return 3;
    } else if (input_buffer.size() >= index + 2) {
        CommandCode command = static_cast<CommandCode>(input_buffer[index + 1]);
        logger->log(Logger::DEBUG, "Received command " + command_code_map.at(command));
        return 2;
    }
    logger->log(Logger::DEBUG, "Received unknown / incomplete command, ignoring");
    return 1;
}
