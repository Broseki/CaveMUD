//
// Created by Travis Canning on 10/26/22.
//

#ifndef CAVEMUD_MASTERCLOCK_H
#define CAVEMUD_MASTERCLOCK_H

#include <mutex>
#include "../Utils/Logger/Logger.h"

class MasterClock {

private:
    enum MasterClockMode {
        SESSION_CONTROLLER,
        ENGINE
    };

    Logger *logger;

    MasterClockMode currentMode;

    std::mutex sessionControllerModeMutex;
    std::mutex engineModeMutex;
    std::mutex readyMutex;
    std::mutex callbackMutex;

    uint32_t sessionControllerThreads;
    uint32_t engineThreads;
    uint32_t callbackCounter;

    void switchModes();
    void allReady();

public:
    MasterClock(Logger *logger, uint32_t sessionControllerThreads, uint32_t engineThreads);

    std::mutex *getSessionControllerModeMutex();
    std::mutex *getEngineModeMutex();
    std::mutex *getReadyMutex();

    void readyCallback();
    void doneCallback();
};


#endif //CAVEMUD_MASTERCLOCK_H
