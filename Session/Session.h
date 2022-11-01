//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SESSION_H
#define CAVEMUD_SESSION_H

#include <vector>
#include <mutex>
#include <unordered_map>
#include "../Engine/StateMachines/StateMachine.h"

class Session {
public:
    Session(int socketfd);

    int get_socketfd();

    // Input buffer methods
    std::vector<char8_t> get_input_buffer();
    void set_input_buffer(std::vector<char8_t> arg_input_buffer);
    void clear_input_buffer();

    // Output buffer methods
    std::vector<char8_t> get_output_buffer();
    void set_output_buffer(std::vector<char8_t> arg_output_buffer);
    void clear_output_buffer();

    void add_state_machine(StateMachine *state_machine);
    void remove_state_machine(StateMachine *state_machine);
    std::vector<StateMachine*> get_state_machines();

    // Logic for session key/value pairs
    void set_kv(std::string key, void* value);
    void* get_kv(std::string key);
    void remove_kv(std::string key);

private:
    // Data
    int socketfd;
    std::vector<char8_t> input_buffer;
    std::vector<char8_t> output_buffer;

    // Mutexes
    std::mutex input_buffer_mutex;
    std::mutex output_buffer_mutex;
    std::mutex state_machine_mutex;
    std::mutex kv_store_mutex;

    // State machines running on this session
    std::vector<StateMachine*> activeStateMachines;

    // Key/value store for session
    std::unordered_map<std::string, void*> kv_store;
};


#endif //CAVEMUD_SESSION_H
