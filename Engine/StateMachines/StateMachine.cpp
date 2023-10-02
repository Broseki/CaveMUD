//
// Created by Travis Canning on 1/25/23.
//

#include "StateMachine.h"

#include <utility>

StateMachine::StateMachine(std::string machine_name) :
    machine_name(std::move(machine_name)),
    m_steppable(true) {}

StateMachine::StateMachine(std::string machine_name, bool steppable) :
    machine_name(std::move(machine_name)),
    m_steppable(true) {}
