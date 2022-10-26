//
// The MasterClock class handles the synchronization between the engine and session controller threads.
// Essentially it will start with the session controller in control, wait for it to finish (keeping track
// using the doneCallback() method), then switch to the engine in control, wait for it to finish, and repeat.
//
// For the ready signal, this is used to ensure that all threads are ready once their section is unlocked. Think
// of it like a man-trap, the mode semaphore is released, then we wait for all threads to reach the ready state, and
// then we lock the mode semaphore again and release the ready semaphore.
//

#include "MasterClock.h"

MasterClock::MasterClock(Logger *logger, uint32_t sessionControllerThreads, uint32_t engineThreads) {
    this->logger = logger;
    this->sessionControllerThreads = sessionControllerThreads;
    this->engineThreads = engineThreads;
    this->callbackCounter = 0;

    // Start in session controller mode
    this->currentMode = SESSION_CONTROLLER;

    // Lock necessary thread controller mutexes to start
    this->engineModeMutex.lock();
    this->readyMutex.lock();

    logger->log(logger->DEBUG, "MasterClock initialized.");
}

void MasterClock::waitOnSessionControllerModeMutex() {
    logger->log(logger->DEBUG, "Waiting on session controller mode mutex");
    const std::lock_guard<std::mutex> lock(this->sessionControllerModeMutex);
}

void MasterClock::waitOnEngineModeMutex() {
    logger->log(logger->DEBUG, "Waiting on engine mode mutex");
    const std::lock_guard<std::mutex> lock(this->engineModeMutex);
}

void MasterClock::waitOnReadyMutex() {
    logger->log(logger->DEBUG, "Waiting on ready mutex");
    const std::lock_guard<std::mutex> lock(this->readyMutex);
}

void MasterClock::readyCallback() {
    const std::lock_guard<std::mutex> lock(this->callbackMutex);
    callbackCounter++;

    logger->log(logger->DEBUG, "MasterClock readyCallback() callbackCounter: " + std::to_string(callbackCounter));

    switch(currentMode) {
        case SESSION_CONTROLLER:
            if (callbackCounter >= sessionControllerThreads) {
                allReady();
            }
            break;
        case ENGINE:
            if (callbackCounter >= engineThreads) {
                allReady();
            }
            break;
    }
}

void MasterClock::doneCallback() {
    const std::lock_guard<std::mutex> lock(this->callbackMutex);
    callbackCounter++;

    logger->log(logger->DEBUG, "MasterClock doneCallback() callbackCounter: " + std::to_string(callbackCounter));

    switch(currentMode) {
        case SESSION_CONTROLLER:
            if (callbackCounter >= sessionControllerThreads) {
                switchModes();
            }
            break;
        case ENGINE:
            if (callbackCounter >= engineThreads) {
                switchModes();
            }
            break;
    }
}

void MasterClock::switchModes() {
    logger->log(logger->DEBUG, "MasterClock switchModes()");

    // Reset callback counter
    callbackCounter = 0;

    // Switch modes
    switch(currentMode) {
        case SESSION_CONTROLLER:
            currentMode = ENGINE;
            break;
        case ENGINE:
            currentMode = SESSION_CONTROLLER;
            break;
    }

    // Lock the ready mutex
    readyMutex.lock();

    // Unlock the mode mutex
    switch(currentMode) {
        case SESSION_CONTROLLER:
            sessionControllerModeMutex.unlock();
            break;
        case ENGINE:
            engineModeMutex.unlock();
            break;
    }

    // Now we wait for ready, the allReady() function will handle things from here

    logger->log(logger->DEBUG, "MasterClock switchModes() complete");
}

void MasterClock::allReady() {
    logger->log(logger->DEBUG, "MasterClock allReady()");

    // Reset callback counter
    callbackCounter = 0;

    // Lock the mode mutex
    switch(currentMode) {
        case SESSION_CONTROLLER:
            sessionControllerModeMutex.lock();
            break;
        case ENGINE:
            engineModeMutex.lock();
            break;
    }

    // Unlock the ready mutex
    readyMutex.unlock();

    // Now we wait for done, the switchModes() function will handle things from here
}
