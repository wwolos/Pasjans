include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

include(CTest)
include(Catch)





add_executable(card_test card_test.cpp ${PROJECT_SOURCE_DIR}/src/card.cpp)
target_include_directories(card_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(card_test PRIVATE ${CMAKE_BINARY_DIR}/_deps/catch2-src/src/catch2)
target_link_libraries(card_test PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(card_test)

add_executable(command_test command_test.cpp ${PROJECT_SOURCE_DIR}/src/command.cpp)
target_include_directories(command_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(command_test PRIVATE ${CMAKE_BINARY_DIR}/_deps/catch2-src/src/catch2)
target_link_libraries(command_test PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(command_test)

add_executable(game_test game_test.cpp ${PROJECT_SOURCE_DIR}/src/game.cpp ${PROJECT_SOURCE_DIR}/src/card.cpp ${PROJECT_SOURCE_DIR}/src/command.cpp) 
target_include_directories(game_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(game_test PRIVATE ${CMAKE_BINARY_DIR}/_deps/catch2-src/src/catch2)
target_link_libraries(game_test PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(game_test)
