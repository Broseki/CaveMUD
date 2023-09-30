//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SESSION_H
#define CAVEMUD_SESSION_H

#include <vector>
#include <mutex>
#include <unordered_map>
#include <memory>
#define BOOST_NO_CXX98_FUNCTION_BASE
#include <boost/any.hpp>

#include "../Engine/StateMachines/StateMachine.h"
#include "../Engine/Views/View.h"

class StateMachine;
class View;

class Session {
public:
    Session(int socketfd);

    int get_socketfd();

    void destroy();

    // Input buffer methods
    std::vector<char8_t> get_input_buffer();
    void set_input_buffer(std::vector<char8_t> arg_input_buffer);
    void clear_input_buffer();

    // Output buffer methods
    std::vector<char8_t> get_output_buffer();
    void set_output_buffer(std::vector<char8_t> arg_output_buffer);
    void clear_output_buffer();

    void add_state_machine(Logger *logger, const std::shared_ptr<StateMachine>& state_machine);
    void remove_state_machine(Logger *logger, const std::shared_ptr<StateMachine>& state_machine);
    void remove_state_machine(Logger *logger, const std::string& machine_name);
    std::vector<std::shared_ptr<StateMachine>> get_state_machines();

    // Logic for session key/value pairs
    void set_kv(const std::string& key, boost::any value);
    boost::any get_kv(const std::string& key);
    void remove_kv(const std::string& key);

    // View set/get logic
    void set_view(Logger* logger, std::shared_ptr<View> view);
    std::shared_ptr<View> get_view();

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
    std::mutex view_mutex;

    // State machines running on this session
    std::vector<std::shared_ptr<StateMachine>> activeStateMachines;

    // Key/value store for session
    std::unordered_map<std::string, boost::any> kv_store;

    // Current view
    std::shared_ptr<View> current_view;
};


#endif //CAVEMUD_SESSION_H
