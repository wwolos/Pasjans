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
    if(!(left.length() == 2 || left.length() == 4 || left.length() == 5) || right.length() != 2){
        isCorrect = false;
        reason = "W poprawnej komendzie left strona(przed dwukropkiem) ma 2 lub 4 znaki, a right 2.";
        return;
    }
    if(!(left[0] == 'k'|| (left[0] == 's' && (left[1] == 'r' || left[1] == 'k')))){
        isCorrect = false;
        reason = "W poprawnej komendzie left strona(przed dwukropkiem) musi zaczynać się od k,sk, lub sr";
        return;
    }
    if(!(right[0] == 'k' ||(right[0] == 's' && right[1] == 'k'))){
        isCorrect = false;
        reason = "W poprawnej komendzie right strona(po dwukropku) musi zaczynać się od k lub sk";
        return;
    }
    if(!(left[0] == 'k' && isdigit(left[1]) && left[1] > '0' && left[1] <= '7')){
        isCorrect = false;
        reason = "Po lewej stronie(przed dwukropkiem) po literze k zawsze musi być numer od 1-7";
        return;
    }
    if(!(right[0] == 'k' && isdigit(right[1]) && right[1] > '0' && right[1] <= '7')){
        isCorrect = false;
        reason = "Po prawej stronie(po dwukropku) po literze k zawsze musi byc liczba od 1-7";
        return;
    }
    if(left.length() == 4 && !(left[2] == 'x' && isdigit(left[3]))){
        isCorrect = false;
        reason = "Jeśli left strona(przed dwukropkiem) ma więcej niż 2 znaki, oznacza to że musi się kończyć na x i liczbe od 1 - 13 1";
        return;
    }
    if(left.length() == 5 && !(left[2] == 'x' && isdigit(left[3]) && isdigit(left[4]))){
        isCorrect = false;
        reason = "Jeśli left strona(przed dwukropkiem) ma więcej niż 2 znaki, oznacza to że musi się kończyć na x i liczbe od 1 - 13 2";
        return;
    }

}

/**
 * @brief Assigns the source type
 * 
 */
void Command::assignSourceType(){
    if(left[0] == 'k'){
        sourceType = 1;
    }
    if(left[0] == 's' && left[1] == 'k'){
        sourceType = 2;
    }
    if(left[0] == 's' && left[1] == 'r'){
        sourceType = 3;
    }
}

/**
 * @brief Assings the type of the destination
 * 
 */
void Command::assignDestinationType(){
    if(right[0] == 'k'){
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
    sourceIndex = left[1]-'0';
    destinationIndex = right[1]-'0';
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