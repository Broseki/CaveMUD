//
// Created by Travis Canning on 10/16/22.
//

#include <iostream>
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

void Session::add_state_machine(std::shared_ptr<StateMachine> state_machine) {
    const std::lock_guard<std::mutex> lock(this->state_machine_mutex);

    this->activeStateMachines.push_back(state_machine);

    for (auto machine: this->activeStateMachines) {
        std::cout << "Machine: " << machine->get_machine_name() << std::endl;
    }
}

void Session::remove_state_machine(std::shared_ptr<StateMachine> state_machine) {
    const std::lock_guard<std::mutex> lock(this->state_machine_mutex);

    this->activeStateMachines.erase(std::remove(this->activeStateMachines.begin(), this->activeStateMachines.end(), state_machine), this->activeStateMachines.end());
}

std::vector<std::shared_ptr<StateMachine>> Session::get_state_machines() {
    const std::lock_guard<std::mutex> lock(this->state_machine_mutex);

    return this->activeStateMachines;
}

void Session::set_kv(std::string key, boost::any value) {
    const std::lock_guard<std::mutex> lock(this->kv_store_mutex);

    this->kv_store[key] = value;
}

boost::any Session::get_kv(std::string key) {
    const std::lock_guard<std::mutex> lock(this->kv_store_mutex);

    return this->kv_store[key];
}

void Session::remove_kv(std::string key) {
    const std::lock_guard<std::mutex> lock(this->kv_store_mutex);

    this->kv_store.erase(key);
}

void Session::set_view(std::shared_ptr<View> view) {
    const std::lock_guard<std::mutex> lock(this->view_mutex);
    this->current_view = view;
}

std::shared_ptr<View> Session::get_view() {
    const std::lock_guard<std::mutex> lock(this->view_mutex);
    return this->current_view;
}

void Session::remove_state_machine(std::string machine_name) {
    const std::lock_guard<std::mutex> lock(this->state_machine_mutex);

    for (auto machine: this->activeStateMachines) {
        if (machine->get_machine_name() == machine_name) {
            this->activeStateMachines.erase(std::remove(this->activeStateMachines.begin(), this->activeStateMachines.end(), machine), this->activeStateMachines.end());
        }
    }
}
