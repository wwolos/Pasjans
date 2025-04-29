#include <iostream>
#include <string>
#include <vector>
#include "card.h"
#include "game.h"

const int EMPTY_LINE_COUNT = 100;

void clearConsole();

int main() {
    clearConsole();
    Game game;

    while(true){
        try{
           game.display(); 
        }
        catch(const std::exception e){
            std::cout << "Wystąpił błąd: " << e.what();
        }
        std::string input;
        std::cin >> input;
        clearConsole();
        if(input == "exit"){
            break;
        }
        try{
            game.processInput(input); 
         }
         catch(const std::exception e){
             std::cout << "Wystąpił błąd: " << e.what();
         }
    }

    clearConsole();
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
