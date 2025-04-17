#ifndef Command_H
#define Command_H

#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "card.h"

/**
 * @brief A class that represents a command
 * 
 */
class Command{
    public:
        Command(std::string input);
        bool isCorrect;
        std::string reason; //Reason for the command being incorrect
        int sourceType; 
        int destinationType;
        int sourceIndex; 
        int destinationIndex; 
        int amountOfCards;

    private:
        std::string left;
        std::string right;

};

#endif