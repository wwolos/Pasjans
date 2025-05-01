/**
 * @file gra.h
 * @author Wiktor Wołos (wiktor_wolos@outlook.com)
 * @brief 
 * @version 1.0
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "card.h"
#include "command.h"



/**
 * @brief A class that handles most of the games logic
 * 
 */
class Game{
    public:
        std::vector<std::vector<Card>> tableau; 
        std::vector<std::vector<Card>> foundation; //The foundation is stored in this order: Trefl(♣) Karo(♦) kier(♥) pik(♠)
        std::vector<Card> waste; //This actully stores the waste and stock
        int wasteIndex = 0; //The index of the first card thats in the waste
        std::vector<std::string> usedCards; //Used for generating random cards
        std::unique_ptr<Command> command;
        std::vector<Card> cardsToMove;
        std::vector<Card> *source;
        std::vector<Card> *destination;
    
        void display(); 
        std::string processInput(std::string input); 
        Game();
    private:
        void controlsInfoMessage();
        void fillInCards();
        void removeEmptyCards();
        int executeCommand();
        void assignSource();
        void getCardsToMove();
        void revertMove();
        bool checkForHiddenCards();
        bool assignDestination();
        bool isCardOrderValid();
        void moveCards();
};

#endif 