cmake_minimum_required(VERSION 3.22)
project(CaveMUD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

set(BOOST_INCLUDE_LIBRARIES thread filesystem system program_options)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)

# Boost does not install correctly using VCPKG on MacOS so we need to use FetchContent
FetchContent_Declare(
        Boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.83.0
)
FetchContent_MakeAvailable(Boost)

# Packages from VCPKG
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

# Generate C++ code from protobuf files
file(GLOB PROTO_FILES ./CaveMUD-Protocol/src/*.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

include_directories(
        ${Protobuf_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
)

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
        Engine/StateMachines/StateMachine.cpp
        ${PROTO_SRCS}
        ${PROTO_HDRS}
)

set_target_properties(CaveMUD PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist
)

target_link_libraries(
        CaveMUD
        ${Protobuf_LIBRARIES}
        Boost::any
        ${nlohmann_json_LIBRARIES}
)
