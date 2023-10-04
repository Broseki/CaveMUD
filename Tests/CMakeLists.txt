find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable(
        CaveMUD_tests
        Hello_test.cpp
)
target_link_libraries(
        CaveMUD_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(CaveMUD_tests)
