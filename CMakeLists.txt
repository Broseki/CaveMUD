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
        Models/ConfigurationModel.cpp Models/ConfigurationModel.h
        Controllers/ConfigurationController.cpp Controllers/ConfigurationController.h
        Controllers/LogController.cpp Controllers/LogController.h
        Models/SessionModel.h
        Controllers/ServerListenerController.cpp Controllers/ServerListenerController.h
        Models/ServerSocketModel.h
        Models/SessionsModel.h Controllers/ServerSocketController.cpp Controllers/ServerSocketController.h Controllers/SessionController.cpp Controllers/SessionController.h Controllers/SessionsController.cpp Controllers/SessionsController.h)

target_link_libraries(
        CaveMUD
        gtest_main
        nlohmann_json::nlohmann_json)
