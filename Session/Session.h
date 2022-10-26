//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SESSION_H
#define CAVEMUD_SESSION_H

#include <vector>
#include <mutex>

class Session {
public:
    Session(int socketfd);

    int get_socketfd();

    std::vector<char8_t> get_input_buffer();
    void set_input_buffer(std::vector<char8_t> arg_input_buffer);
    void clear_input_buffer();

    std::vector<char8_t> get_output_buffer();
    void set_output_buffer(std::vector<char8_t> arg_output_buffer);
    void clear_output_buffer();

private:
    // Data
    int socketfd;
    std::vector<char8_t> input_buffer;
    std::vector<char8_t> output_buffer;

    // Mutexes
    std::mutex input_buffer_mutex;
    std::mutex output_buffer_mutex;
};


#endif //CAVEMUD_SESSION_H
