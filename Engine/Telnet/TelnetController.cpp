//
// Created by Travis Canning on 11/7/22.
//

#include "TelnetController.h"
#include "../../Utils/Configuration/Configuration.h"
#include "Handlers/CommandHandlers/CommandRouter.h"
#include "../../Session/KV_Keys.h"
#include "Handlers/OptionHandlers/OptionRouter.h"

void TelnetController::handleCommands(Logger *logger, Configuration* config, std::shared_ptr<Session> session) {
    std::vector<char8_t> input_buffer = session->get_input_buffer();

    // Loop through the input buffer, and handle each command that we find
    // Remove the command from the input buffer once it's been handled
    uint32_t index = 0;
    while (index < input_buffer.size()) {
        if (input_buffer[index] == IAC) {
            uint32_t bytes_consumed = handleCommand(logger, config, session, input_buffer, index);
            input_buffer.erase(input_buffer.begin() + index, input_buffer.begin() + index + bytes_consumed);
        } else {
            index++;
        }
    }

}

std::vector<char8_t> TelnetController::constructCommand(CommandCode command) {
    std::vector<char8_t> command_buffer = {IAC, static_cast<char8_t>(command)};
    return command_buffer;
}

std::vector<char8_t> TelnetController::constructCommand(CommandCode command, OptionCode option) {
    std::vector<char8_t> command_buffer = {IAC, static_cast<char8_t>(command), static_cast<char8_t>(option)};
    return command_buffer;
}

std::vector<char8_t> TelnetController::constructCommand(CommandCode command, OptionCode option, const std::vector<char8_t>& extra_data) {
    std::vector<char8_t> command_buffer = {IAC, static_cast<char8_t>(command), static_cast<char8_t>(option)};
    command_buffer.insert(command_buffer.end(), extra_data.begin(), extra_data.end());
    return command_buffer;
}

uint32_t TelnetController::handleCommand(Logger *logger, Configuration* config, const std::shared_ptr<Session>& session, const std::vector<char8_t>& input_buffer,
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
        logger->log(Logger::DEBUG, "Received command " + command_code_string_map.at(command) + " for option " +
                                   option_code_string_map.at(option));

        // Handle the command
        OptionRouter::routeOption(logger, config, session, command, option, std::vector<char8_t>());

        return 3;
    } else if (input_buffer.size() >= index + 2 && input_buffer[index + 1] == SB) {
        // Handle if the IAC is followed by SB
        // Find the end of the subnegotiation
        uint32_t end_index = index + 2;
        while (end_index < input_buffer.size() && !(input_buffer[end_index] == IAC && input_buffer[end_index + 1] == SE)) {
            end_index++;
        }
        if (end_index >= input_buffer.size()) {
            logger->log(Logger::WARNING, "Received incomplete subnegotiation, ignoring");
            return 2;
        }
        OptionCode option = static_cast<OptionCode>(input_buffer[index + 2]);
        std::vector<char8_t> sb_data(input_buffer.begin() + index + 3, input_buffer.begin() + end_index);
        logger->log(Logger::DEBUG, "Received subnegotiation for option " + option_code_string_map.at(option));

        // Handle subnegotiation data
        OptionRouter::routeOption(logger, config, session, SB, option, sb_data);

        return end_index - index + 2;
    } else if (input_buffer.size() >= index + 2) {
        CommandCode command = static_cast<CommandCode>(input_buffer[index + 1]);
        logger->log(Logger::DEBUG, "Received command " + command_code_string_map.at(command));
        CommandRouter::routeCommand(logger, config, session, command);
        return 2;
    }
    logger->log(Logger::WARNING, "Received unknown / incomplete command, ignoring");
    return 1;
}

void TelnetController::addToCommandAppendBuffer(Logger *logger, const std::shared_ptr<Session> &session,
                                                std::vector<char8_t> bytes) {
    logger->log(Logger::DEBUG, "Adding " + std::to_string(bytes.size()) + " bytes to command append buffer");
    if (session->get_kv(SESSION_KV_COMMAND_APPEND_BUFFER).empty()) {
        session->set_kv(SESSION_KV_COMMAND_APPEND_BUFFER, bytes);
    } else {
        std::vector<char8_t> append_buffer = boost::any_cast<std::vector<char8_t>>(session->get_kv(SESSION_KV_COMMAND_APPEND_BUFFER));
        append_buffer.insert(append_buffer.end(), bytes.begin(), bytes.end());
        session->set_kv(SESSION_KV_COMMAND_APPEND_BUFFER, append_buffer);
    }
}

void TelnetController::addToCommandPrependBuffer(Logger *logger, const std::shared_ptr<Session> &session,
                                                 std::vector<char8_t> bytes) {
    logger->log(Logger::DEBUG, "Adding " + std::to_string(bytes.size()) + " bytes to command append buffer");
    if (session->get_kv(SESSION_KV_COMMAND_PREPEND_BUFFER).empty()) {
        session->set_kv(SESSION_KV_COMMAND_PREPEND_BUFFER, bytes);
    } else {
        std::vector<char8_t> prepend_buffer = boost::any_cast<std::vector<char8_t>>(session->get_kv(SESSION_KV_COMMAND_PREPEND_BUFFER));
        prepend_buffer.insert(prepend_buffer.end(), bytes.begin(), bytes.end());
        session->set_kv(SESSION_KV_COMMAND_PREPEND_BUFFER, prepend_buffer);
    }
}
