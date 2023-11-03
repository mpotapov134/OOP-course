cmake_minimum_required(VERSION 3.16)
project(CircularBuffer)

set(CMAKE_CXX_STANDARD 14)
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
    CircularBufferTests
    src/tests/AccessTest.cpp
    src/tests/ConstrTest.cpp
    src/tests/EraseTest.cpp
    src/tests/InsertTest.cpp
    src/tests/PopTest.cpp
    src/tests/PushTest.cpp
    src/tests/RotateTest.cpp
    src/tests/SetCapacityTest.cpp
)

target_link_libraries(
    CircularBufferTests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(CircularBufferTests)
