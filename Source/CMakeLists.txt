cmake_minimum_required(VERSION 3.5)

project(RunGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RunGame
    main.cpp
    ship.cpp
    rockets.cpp
    GlobalVariables.cpp
    laser.cpp
    Improvements.cpp
    framework.cpp
    CosmoStation.cpp
    clissans.cpp
    asteroids.cpp
    menus.cpp
    smoke.cpp)


target_link_libraries(RunGame ${CMAKE_SOURCE_DIR}/libs/libsfml-audio.so.2.4)
target_link_libraries(RunGame ${CMAKE_SOURCE_DIR}/libs/libsfml-graphics.so.2.4)
target_link_libraries(RunGame ${CMAKE_SOURCE_DIR}/libs/libsfml-system.so.2.4)
target_link_libraries(RunGame ${CMAKE_SOURCE_DIR}/libs/libsfml-window.so.2.4)
target_link_libraries(RunGame ${CMAKE_SOURCE_DIR}/libs/libopenal.so.1)
target_link_libraries(RunGame ${CMAKE_SOURCE_DIR}/libs/libopenal.so.1.18.2)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
