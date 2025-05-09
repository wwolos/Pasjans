#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "card.h"
#include "game.h"

const int EMPTY_LINE_COUNT = 100;
const std::string LOG_PATH = "../logs/";

std::ofstream logFile;


void clearConsole();
void initializeLogger();
void log(std::string text);

int main() {
    clearConsole();
    std::ofstream logFile;
    initializeLogger();
    log("Initializing game...");
    Game game;
    log("Game fully initialized");


    while(true){
        try{
           game.display(); 
        }
        catch(const std::exception e){
            std::cout << "Wystąpił błąd: " << e.what();
            log("While executing game.display() an error has occured");
            log(e.what());
        }
        std::string input;
        log("Waiting for input...");
        std::cin >> input;
        log("Input read:");
        log(input);
        log("Clearing console...");
        clearConsole();
        log("Console cleaned");
        if(input == "exit"){
            break;
        }
        try{
            log(game.processInput(input)); 
         }
         catch(const std::exception e){
            std::cout << "Wystąpił błąd: " << e.what();
            log("While executing game.processInput(input) an error has occured");
            log(e.what());
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
 * @brief A little function to clear up the console by printing out a configured amount of empty lines
 * 
 */
void clearConsole(){ 
    for(int i = 0; i < EMPTY_LINE_COUNT; i++){
        std::cout << "\n";
    }
}

void initializeLogger(){
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    char logFileName[100];
    strftime(logFileName, 100, "%F-%T.log", &datetime);
    logFile.open(LOG_PATH+logFileName);
}

void log(std::string text){
    logFile << text << "\n";
}
