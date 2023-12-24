cmake_minimum_required(VERSION 3.16)
project(GameTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ReaderTest
    src/Reader.cpp
    tests/ReaderTest.cpp
)

add_executable(
    UniverseTest
    src/Universe.cpp
    tests/UniverseTest.cpp
)

target_link_libraries(
    ReaderTest
    GTest::gtest_main
)

target_link_libraries(
    UniverseTest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ReaderTest)
gtest_discover_tests(UniverseTest)
