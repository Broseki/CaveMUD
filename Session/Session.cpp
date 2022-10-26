//
// Created by Travis Canning on 10/16/22.
//

#include "Session.h"

Session::Session(int socketfd) {
    this->socketfd = socketfd;
}

int Session::get_socketfd() {
    return this->socketfd;
}

std::vector<char8_t> Session::get_input_buffer() {
    const std::lock_guard<std::mutex> lock(this->input_buffer_mutex);

    this->input_buffer.clear();
    return this->input_buffer;
}

void Session::set_input_buffer(std::vector<char8_t> arg_input_buffer) {
    const std::lock_guard<std::mutex> lock(this->input_buffer_mutex);

    this->input_buffer = arg_input_buffer;
}

void Session::clear_input_buffer() {
    const std::lock_guard<std::mutex> lock(this->input_buffer_mutex);

    this->input_buffer.clear();
}

std::vector<char8_t> Session::get_output_buffer() {
    const std::lock_guard<std::mutex> lock(this->output_buffer_mutex);

    this->output_buffer.clear();
    return this->output_buffer;
}

void Session::set_output_buffer(std::vector<char8_t> arg_output_buffer) {
    const std::lock_guard<std::mutex> lock(this->output_buffer_mutex);

    this->output_buffer = arg_output_buffer;
}

void Session::clear_output_buffer() {
    const std::lock_guard<std::mutex> lock(this->output_buffer_mutex);

    this->output_buffer.clear();
}
