//
// Created by Travis Canning on 10/31/22.
//

#ifndef CAVEMUD_STATEMACHINE_H
#define CAVEMUD_STATEMACHINE_H

class StateMachine {
public:
    virtual void update() = 0;
    virtual void reset() = 0;
};

#endif //CAVEMUD_STATEMACHINE_H
