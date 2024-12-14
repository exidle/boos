cmake_minimum_required(VERSION 3.15)
project(boosapi CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Crow REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(boosapi src/seat.cpp src/boosapi.cpp src/room.cpp src/theater.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

target_include_directories(boosapi PUBLIC include)

set_target_properties(boosapi PROPERTIES PUBLIC_HEADER "include/boosapi.h")

install(TARGETS boosapi PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/boosapi)

target_include_directories(${PROJECT_NAME} PRIVATE ${CROW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME})

add_executable(boos src/main.cpp)
target_link_libraries(boos boosapi Crow::Crow)
