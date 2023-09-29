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

find_package(Protobuf CONFIG REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})

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
        Engine/Views/View.h
        Engine/StateMachines/StateMachine.h
        Engine/StateMachines/Echo.cpp Engine/StateMachines/Echo.h
        Engine/Views/EchoView.cpp Engine/Views/EchoView.h
        Session/KV_Keys.h
        Engine/StateMachines/ReverseEcho.cpp
        Engine/StateMachines/ReverseEcho.h
        Engine/StateMachines/StateMachine.cpp)

target_link_libraries(
        CaveMUD
        nlohmann_json::nlohmann_json
        Boost::any
        ${Protobuf_LIBRARIES}
)
