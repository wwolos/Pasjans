cmake_minimum_required(VERSION 3.10)

project(Pasjans)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O0")
# set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")


add_executable(Pasjans 
                src/main.cpp 
                src/card.cpp 
                src/game.cpp 
                src/command.cpp
                src/gameView.cpp
)

target_include_directories(Pasjans PUBLIC include)

enable_testing()
add_subdirectory(tests)