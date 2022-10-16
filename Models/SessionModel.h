//
// Created by Travis Canning on 10/15/22.
//

#ifndef CAVEMUD_SESSIONMODEL_H
#define CAVEMUD_SESSIONMODEL_H

#include <string>
#include <vector>
#include <mutex>

class SessionModel {

public:
    // Data
    int socketfd;
    std::vector<std::string> input_buffer_queue;
    std::string output_buffer;

    // Mutexes
    std::mutex input_buffer_mutex;
    std::mutex output_buffer_mutex;
};


#endif //CAVEMUD_SESSIONMODEL_H
