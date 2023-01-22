cmake_minimum_required(VERSION 3.22)
project(CaveMUD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

set(BOOST_INCLUDE_LIBRARIES thread filesystem system program_options)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)

FetchContent_Declare(
        Boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.80.0
)

FetchContent_MakeAvailable(
        json
        Boost)

enable_testing()

add_executable(
        CaveMUD
        main.h main.cpp
        Utils/Configuration/Configuration.cpp Utils/Configuration/Configuration.h
        Utils/Logger/Logger.cpp Utils/Logger/Logger.h
        Networking/Server/ServerListener.cpp Networking/Server/ServerListener.h
        Networking/Server/ServerSocket.cpp Networking/Server/ServerSocket.h
        Session/Session.cpp Session/Session.h
        Session/Sessions.cpp Session/Sessions.h
        Engine/GameLoop.cpp Engine/GameLoop.h
        Engine/MasterClock.cpp Engine/MasterClock.h
        Session/SessionHandler.cpp Session/SessionHandler.h
        Engine/Telnet/TelnetConstants.h
        Engine/Views/View.h
        Engine/StateMachines/StateMachine.h
        Engine/StateMachines/Echo.cpp Engine/StateMachines/Echo.h
        Engine/Views/EchoView.cpp Engine/Views/EchoView.h
        Engine/Telnet/TelnetController.cpp Engine/Telnet/TelnetController.h
        Engine/Telnet/Handlers/OptionHandlers/TelnetOptionHandler.h Engine/Telnet/Handlers/CommandHandlers/TelnetCommandHandler.h Engine/Telnet/Handlers/CommandHandlers/CommandRouter.cpp Engine/Telnet/Handlers/CommandHandlers/CommandRouter.h Engine/Telnet/Handlers/OptionHandlers/OptionRouter.cpp Engine/Telnet/Handlers/OptionHandlers/OptionRouter.h Engine/Telnet/Handlers/CommandHandlers/AreYouThere.cpp Engine/Telnet/Handlers/CommandHandlers/AreYouThere.h Session/KV_Keys.h Engine/Telnet/Handlers/CommandHandlers/InterruptProcess.cpp Engine/Telnet/Handlers/CommandHandlers/InterruptProcess.h Engine/StateMachines/ReverseEcho.cpp Engine/StateMachines/ReverseEcho.h Engine/Telnet/Handlers/OptionHandlers/TimingMark.cpp Engine/Telnet/Handlers/OptionHandlers/TimingMark.h Engine/Views/View.cpp Engine/Telnet/Handlers/OptionHandlers/LineMode.cpp Engine/Telnet/Handlers/OptionHandlers/LineMode.h Engine/Telnet/Handlers/OptionHandlers/SupressGoAhead.cpp Engine/Telnet/Handlers/OptionHandlers/SupressGoAhead.h Engine/Telnet/Handlers/OptionHandlers/TelnetOptionEcho.cpp Engine/Telnet/Handlers/OptionHandlers/TelnetOptionEcho.h)

target_link_libraries(
        CaveMUD
        nlohmann_json::nlohmann_json
        Boost::any)
