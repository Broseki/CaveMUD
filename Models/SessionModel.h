//
// Created by Travis Canning on 10/15/22.
//

#ifndef CAVEMUD_SESSIONMODEL_H
#define CAVEMUD_SESSIONMODEL_H

#include <string>
#include <vector>

class SessionModel {

public:
    // Data
    uint32_t id;
    int socketfd;
    std::vector<std::string> input_buffer;
    std::string output_buffer;

    // Semaphores

};


#endif //CAVEMUD_SESSIONMODEL_H
