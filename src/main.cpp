/**
 * @file main.cpp
 * @author Wiktor Wołos (wiktor_wolos@outlook.com)
 * @brief Main file of the game
 * @version 0.1
 * @date 2025-05-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#define NOMINMAX  // Stop windows compiler "cl.exe" from bitching
#include <Pasjans/card.h>
#include <Pasjans/game.h>
#include <Pasjans/gameView.h>

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

const int LOG_NAME_SIZE = 100;
const std::string LOG_PATH = "../logs/";

std::ofstream logFile;

void clearConsole();
void initializeLogger();
void log(std::string text);
bool handleInput(std::string input, Game &game, GameView &gameView);

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");  // Set UTF-8 encoding on Windows
#endif

    clearConsole();
    std::ofstream logFile;
    initializeLogger();
    log("Initializing game...");
    Game game;
    GameView gameView;
    log("Game fully initialized");
    clearConsole();

    while (true) {
        try {
            if (game.displayMode == Game::DisplayMode::SAFE) {
                gameView.safeDisplay(game.tableau, game.foundation, game.waste, game.wasteIndex);
            }
            if (game.displayMode == Game::DisplayMode::NORMAL) {
                gameView.normalDisplay(game.tableau, game.foundation, game.waste, game.wasteIndex);
            }
        } catch (const std::exception e) {
            std::cout << "Wystąpił błąd: " << e.what();
            log("While executing game.display() an error has occured");
            log(e.what());
        }

        std::string input;
        log("Waiting for input...");
        std::cin >> input;

        if (!handleInput(input, game, gameView)) break;

        if (game.checkForWin()) {
            gameView.winScreen();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        logFile.flush();
    }

    log("Exiting game");
    clearConsole();
    logFile.flush();
    logFile.close();
    return 0;
}

/**
 * @brief A little function to clear up the console
 *
 */
void clearConsole() { std::cout << "\033[2J\033[1;1H"; }

/**
 * @brief Initializes the logger
 *
 */
void initializeLogger() {
    try {
        if (!std::filesystem::exists(LOG_PATH)) {
            std::filesystem::create_directory(LOG_PATH);
        }
    } catch (const std::exception e) {
        std::cout << "Wystąpił błąd podczas tworzania folderu z logami: " << e.what();
    }
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    char logFileName[LOG_NAME_SIZE];
    strftime(logFileName, LOG_NAME_SIZE, "%F-%T.log", &datetime);
    logFile.open(LOG_PATH + logFileName);
}

/**
 * @brief Logs text into the log file
 *
 * @param text the text to log
 */
void log(std::string text) { logFile << text << std::endl; }

/**
 * @brief Handles the input
 *
 * @param input The input to handle
 * @param game The game object
 * @return true If sucessfull and should continue
 * @return false If the game should end
 */
bool handleInput(std::string input, Game &game, GameView &gameView) {
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });  // Convert to lower case
    log("Input read:");
    log(input);
    log("Clearing console...");
    clearConsole();
    log("Console cleaned");
    if (input == "exit") {
        gameView.giveUpScreen();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return false;
    }
    if (input == "settings") {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        game.settingsPopup(false);
        return true;
    }
    try {
        log(game.processInput(input));
    } catch (const std::exception e) {
        std::cout << "Wystąpił błąd: " << e.what();
        log("While executing game.processInput(input) an error has "
            "occured");
        log(e.what());
    }
    return true;
}
