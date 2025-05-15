#ifndef Command_H
#define Command_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <Pasjans/card.h>

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
        bool isWasteScroll = false;
        bool isFullColumMove = false;

    private:
        std::string left;
        std::string right;
        void validateCommand();
        void assignSourceType();
        void assignDestinationType();
        void assignTheIndices();
        void checkTheAmount();
        bool isSourceAColumn;
        bool isDestinationAColumn;

};

#endif