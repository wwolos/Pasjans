#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <Pasjans/card.h>
#include <Pasjans/game.h>

#ifdef _WIN32
    system("chcp 65001 > nul"); // Set UTF-8 encoding on Windows
#endif


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
    game.tableau = {{Card(4, 0),Card(3, 1), Card(2, 0), Card(1,1)},{Card(5,2),Card(5,1)},{},{},{},{},{}};
    game.tableau[1][0].hide();
    log("Game fully initialized");
    clearConsole();


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
        std::transform(input.begin(), input.end(), input.begin(),[](unsigned char c){ return std::tolower(c); }); // Convert to lower case
        log("Input read:");
        log(input);
        log("Clearing console...");
        clearConsole();
        log("Console cleaned");
        if(input == "exit"){
            break;
        }
        if(input == "settings"){
            game.settingsPopup(false);
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
    std::cout << "\033[2J\033[1;1H";
}

void initializeLogger(){
    try{
        if(!std::filesystem::exists(LOG_PATH)){
            std::filesystem::create_directory(LOG_PATH);
        } 
    }
    catch(const std::exception e){
        std::cout << "Wystąpił błąd podczas tworzania folderu z logami: " << e.what();
    }
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    char logFileName[100];
    strftime(logFileName, 100, "%F-%T.log", &datetime);
    logFile.open(LOG_PATH+logFileName);
}

void log(std::string text){
    logFile << text << "\n";
}
