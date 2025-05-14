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
#include <rang/rang.hpp>
#include <Pasjans/command.h>
#include <Pasjans/card.h>



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

        void settingsPopup(bool isFirstTime);
        void display(); 
        std::string processInput(std::string input); 
        Game();
    private:
        enum class CommandExecutionResult{
            SUCCESS,
            UNABLE_TO_GET_CARDS_TO_MOVE,
            UNABLE_TO_CHECK_FOR_HIDDEN_CARDS,
            UNABLE_TO_ASSIGN_DESTINATION,
            UNABLE_TO_CHECK_CARD_ORDER
        };
        enum class DisplayMode{
            NORMAL,
            SAFE,
            NONE
        };
        DisplayMode displayMode;
        const std::string SEPARATOR30 = "=============================";
        const std::string SEPARATOR44 = "===========================================";
        void controlsInfoMessage();
        void fillInCards();
        void removeEmptyCards();
        CommandExecutionResult executeCommand();
        void assignSource();
        bool getCardsToMove();
        void revertMove();
        bool checkForHiddenCards();
        bool assignDestination();
        bool isCardOrderValid();
        void moveCards();
        void normalDisplay();
        void safeDisplay();
        int checkLongestColumn();
        

        
};

#endif 