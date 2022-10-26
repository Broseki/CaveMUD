cmake_minimum_required(VERSION 3.22)
project(CaveMUD)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(
        googletest
        json)

enable_testing()

add_executable(
        CaveMUD
        main.h main.cpp
        Utils/Configuration/Configuration.cpp Utils/Configuration/Configuration.h
        Utils/Logger/Logger.cpp Utils/Logger/Logger.h
        Networking/Server/ServerListener.cpp Networking/Server/ServerListener.h
        Networking/Server/ServerSocket.cpp Networking/Server/ServerSocket.h Session/Session.cpp Session/Session.h Session/Sessions.cpp Session/Sessions.h Engine/GameLoop.cpp Engine/GameLoop.h Engine/MasterClock.cpp Engine/MasterClock.h Session/SessionHandler.cpp Session/SessionHandler.h)

target_link_libraries(
        CaveMUD
        gtest_main
        nlohmann_json::nlohmann_json)
