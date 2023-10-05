find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(
        CaveMUD_tests
        Utils/Logger/Logger_test.cpp
)
target_link_libraries(
        CaveMUD_tests
        GTest::gtest_main
        CaveMUD
)

include(GoogleTest)
gtest_discover_tests(CaveMUD_tests)
