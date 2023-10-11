find_package(GTest CONFIG REQUIRED)
FIND_LIBRARY(GOOGLE_MOCK gmock)

enable_testing()

# Copy the test configuration file to the build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Utils/Configuration/test_config.json ${CMAKE_CURRENT_BINARY_DIR}/test_config.json COPYONLY)

add_executable(
        CaveMUD_tests
        Utils/Logger/Logger_test.cpp
        Utils/Configuration/Configuration_test.cpp
        Session/Sessions_test.cpp
        Session/Session_test.cpp
)
target_link_libraries(
        CaveMUD_tests
        GTest::gtest_main
        GTest::gmock_main
        CaveMUD
)

include(GoogleTest)
gtest_discover_tests(CaveMUD_tests)
