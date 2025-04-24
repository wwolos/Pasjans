#include "command.h"

/**
 * @brief Checks if the command is correct, and splits up the informations into smaller pieces
 * 
 * @param input The command to be processed
 */
Command::Command(std::string input){
    isCorrect = true;
    left = input.substr(0,input.find(":"));
    right = input.substr(input.find(":")+1);
    validateCommand();
    assignDestinationType();
    assignSourceType();
    assignTheIndices();
    checkTheAmount();
}

/**
 * @brief Check if the command is valid
 * 
 */
void Command::validateCommand(){
    isSourceAColumn = left[0] == 'k';
    isDestinationAColumn = right[0] == 'k';
    bool isLeftLengthValid = (left.length() == 2 || left.length() == 4 || left.length() == 5);
    bool isRightLengthValid = (right.length() == 2);
    bool isDestinationFoundation = right.substr(0,2) == "sk";
    bool isCardAmountValid = left[2] == 'x' && isdigit(left[3]);
    bool isDestinationColumnNumberValid = right[1] > '0' && right[1] <= '7';
    bool isSourceColumnNumberValid = left[1] > '0' && left[1] <= '7';
    bool isSourceStock = left.substr(0,2) == "sr";

    if(!(isDestinationAColumn || isDestinationFoundation)){
        isCorrect = false;
        reason = "W poprawnej komendzie prawa strona (po dwukropku) musi zaczynać się od k lub sk";
        return;
    }
    if(isDestinationAColumn){
        if(!isDestinationColumnNumberValid){
            isCorrect = false;
            reason = "Po prawej stronie (po dwukropku) po literze k zawsze musi byc liczba od 1-7";
            return;
        }
    }

    if(!(isSourceAColumn || isSourceStock)){
        isCorrect = false;
        reason = "W poprawnej komendzie lewa strona (przed dwukropkiem) musi zaczynać się od k lub sr";
        return;
    }
    if(isSourceAColumn){
        if(!isSourceColumnNumberValid){
            isCorrect = false;
            reason = "Po lewej stronie (przed dwukropkiem) po literze k zawsze musi być numer od 1-7";
            return;
        }
    }

    if(!(isLeftLengthValid && isRightLengthValid)){
        isCorrect = false;
        reason = "W poprawnej komendzie lewa strona (przed dwukropkiem) ma 2 lub 4 znaki, a prawa 2.";
        return;
    }

    if(left.length() == 4){
        if(!isCardAmountValid){
            isCorrect = false;
            reason = "Jeśli lewa strona (przed dwukropkiem) ma więcej niż 2 znaki, oznacza to że musi się kończyć na x i liczbe od 1 - 13 1";
            return;
        }
    }
    if(left.length() == 5){
        if(!(isCardAmountValid && isdigit(left[4]))){
            isCorrect = false;
            reason = "Jeśli lewa strona (przed dwukropkiem) ma więcej niż 2 znaki, oznacza to że musi się kończyć na x i liczbe od 1 - 13 2";
            return;
        }
    }

}

/**
 * @brief Assigns the source type
 * 
 */
void Command::assignSourceType(){
    if(isSourceAColumn){
        sourceType = 1;
    }
    if(left[0] == 's' && left[1] == 'r'){
        sourceType = 2;
    }
}

/**
 * @brief Assings the type of the destination
 * 
 */
void Command::assignDestinationType(){
    if(isDestinationAColumn){
        destinationType = 1;
    }
    else{
        destinationType = 2;
    }
}

/**
 * @brief Assigns the indieces
 * 
 */
void Command::assignTheIndices(){
    sourceIndex = left[1]-'0'-1;
    destinationIndex = right[1]-'0'-1;
}

/**
 * @brief Checks the amount of cards that need to be moved
 * 
 */
void Command::checkTheAmount(){
    if(left.length() == 4){
        amountOfCards = left[3]-'0';
    }
    else if(left.length() == 5){
        amountOfCards = std::stoi(left.substr(3,2));
    }
    else{
        amountOfCards = 1;
    }
}