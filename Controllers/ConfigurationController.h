//
// Created by Travis Canning on 10/14/22.
//

#ifndef CAVEMUD_CONFIGURATIONCONTROLLER_H
#define CAVEMUD_CONFIGURATIONCONTROLLER_H

#include <string>

#include "../Models/ConfigurationModel.h"

class ConfigurationController {

public:
    ConfigurationModel getConfiguration(std::string configuration_file_path);
};


#endif //CAVEMUD_CONFIGURATIONCONTROLLER_H
