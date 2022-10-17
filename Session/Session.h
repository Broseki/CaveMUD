//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SESSION_H
#define CAVEMUD_SESSION_H

#include <string>
#include <mutex>

class Session {
public:
    Session(int socketfd);

    int get_socketfd();

private:
    // Data
    int socketfd;
    std::string input_buffer_queue;
    std::string output_buffer;

    // Mutexes
    std::mutex input_buffer_mutex;
    std::mutex output_buffer_mutex;
};


#endif //CAVEMUD_SESSION_H
