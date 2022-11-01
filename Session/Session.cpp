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

void Session::add_state_machine(StateMachine *state_machine) {
    const std::lock_guard<std::mutex> lock(this->state_machine_mutex);

    if (std::find(this->activeStateMachines.begin(), this->activeStateMachines.end(), state_machine) == this->activeStateMachines.end()) {
        this->activeStateMachines.push_back(state_machine);
    }
}

void Session::remove_state_machine(StateMachine *state_machine) {
    const std::lock_guard<std::mutex> lock(this->state_machine_mutex);

    this->activeStateMachines.erase(std::remove(this->activeStateMachines.begin(), this->activeStateMachines.end(), state_machine), this->activeStateMachines.end());
}

std::vector<StateMachine *> Session::get_state_machines() {
    const std::lock_guard<std::mutex> lock(this->state_machine_mutex);

    return this->activeStateMachines;
}

void Session::set_kv(std::string key, std::shared_ptr<boost::any> value) {
    const std::lock_guard<std::mutex> lock(this->kv_store_mutex);

    this->kv_store[key] = value;
}

std::shared_ptr<boost::any> Session::get_kv(std::string key) {
    const std::lock_guard<std::mutex> lock(this->kv_store_mutex);

    return this->kv_store[key];
}

void Session::remove_kv(std::string key) {
    const std::lock_guard<std::mutex> lock(this->kv_store_mutex);

    this->kv_store.erase(key);
}
