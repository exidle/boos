cmake_minimum_required(VERSION 3.15)
project(test_package CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(boosapi CONFIG REQUIRED)
find_package(GTest REQUIRED)

add_executable(test_package test_room.cpp test_theater.cpp test_seat.cpp)
target_link_libraries(test_package boosapi::boosapi GTest::gtest_main GTest::gtest)

