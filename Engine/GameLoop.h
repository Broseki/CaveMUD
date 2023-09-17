//
// Created by Travis Canning on 10/25/22.
//

#ifndef CAVEMUD_GAMELOOP_H
#define CAVEMUD_GAMELOOP_H

#define BOOST_NO_CXX98_FUNCTION_BASE
#include <boost/any.hpp>

#include "../Utils/Logger/Logger.h"
#include "../Utils/Configuration/Configuration.h"
#include "MasterClock.h"
#include "../Session/Sessions.h"

class GameLoop {
private:
    Logger *logger;
    Configuration *configuration;
    MasterClock *master_clock;
    Sessions *sessions;
    bool stopped;
    uint32_t thread_id;

    // Static global variables (for all game loops)
    static std::mutex global_kv_mutex;
    static std::unordered_map<std::string, boost::any> global_kv_store;

    void handleSession(const std::shared_ptr<Session>& session);

public:
    GameLoop(Logger *logger, Configuration *configuration, MasterClock *master_clock, Sessions *sessions, uint32_t thread_id);
    ~GameLoop();

    void start();
    void stop();

    // Static methods for global variables
    static void set_global(std::string key, boost::any value) {
        std::lock_guard<std::mutex> lock(global_kv_mutex);
        global_kv_store[key] = value;
    }
    static boost::any get_global(std::string key) {
        std::lock_guard<std::mutex> lock(global_kv_mutex);
        return global_kv_store[key];
    }
    static void remove_global(std::string key) {
        std::lock_guard<std::mutex> lock(global_kv_mutex);
        global_kv_store.erase(key);
    }
};


#endif //CAVEMUD_GAMELOOP_H
