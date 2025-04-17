cmake_minimum_required(VERSION 3.10)

project(Pasjans)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(Pasjans src/main.cpp src/card.cpp src/game.cpp src/command.cpp)
