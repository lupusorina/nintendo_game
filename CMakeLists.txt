cmake_minimum_required(VERSION 2.6)

project(unittest-build)
set(CMAKE_BUILD_TYPE Debug)



SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")


add_executable(
    unittests
    ./source/tests/runner.cpp
    ./source/tests/test.cpp
    )

target_link_libraries(
    unittests
    m
    CppUTest
    CppUTestExt
    )

target_include_directories(unittests PUBLIC ./source/tests)

add_custom_target(check ./unittests DEPENDS unittests)
