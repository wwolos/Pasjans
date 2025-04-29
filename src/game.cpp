#include "game.h"


/**
 * @brief Display welcome message, setup the tableau, foundataion etc. 
 * 
 */
Game::Game(){
    srand(time(0)); //Make sure the RNG has a different seed so it doesn't generate the same numbers
    tableau.resize(7); 
    foundation.resize(4);
    fillInCards();
    removeEmptyCards();
    controlsInfoMessage();
    
}

/**
 * @brief Displays the game(tableau, foundation, stock&waste)
 * 
 */
void Game::display(){
    //Check the length of the longest column in the tableau
    int longestColumn = 0; 
    for(const auto& column : tableau){ 
        if(column.size() > longestColumn){ 
            longestColumn = column.size();
        }
    }

    std::cout << "\n=============================\n|";

    //Display the foundation
    for(int i = 0; i < 4; i++){
        if(foundation[i].size() >= 1){
            std::cout << foundation[i][foundation[i].size()-1].text << "|";
        }
        else{
            switch(i){
                case(0):
                    std::cout << " ♣ |";
                    break;
                case(1):
                    std::cout << " ♦ |";
                    break;
                case(2):
                    std::cout << " ♥ |";
                    break;
                case(3):
                    std::cout << " ♠ |";
                    break;

            }
        }
    }

    //Display the waste/stock
    if(waste.size() > 0){
        std::cout << "   |XX |" << waste[wasteIndex].text << "|"; 
    }
    else{
        std::cout << "   |XX |XX |";
    }

    std::cout << "\n=============================";

    //Display the tableau
    for(int i = 0; i < longestColumn; i++){ 
        std::cout << "\n|";
        for(const auto& column : tableau){ 
            if(i < column.size()){ 
                std::cout << column[i].text << "|"; 
            }
            else{ 
                std::cout << "   |";
            }
        }
    }

    std::cout << "\n=============================\n| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n=============================\n";
}

/**
 * @brief A function that chcecks if the input is a correct command(using Command), and if its correct executes it
 * 
 * @param input The input to check and execute
 */
void Game::processInput(std::string input){
    command = std::make_unique<Command>(input);
    if(command->isCorrect){
        std::cout << input;
    }
    else{
        std::cout << "Komenda: " << input << " jest niepoprawna, ponieważ:\n" << command->reason;
        return;
    }
    executeCommand();
}


/**
 * @brief A function that displays informations about the game controls
 * 
 */
void Game::controlsInfoMessage(){
    std::cout << "Witaj w grze: Pasjans\n";
    std::cout << "Aby sterować w tej grze będziesz używać komend\n";
    std::cout << "Każda komenda składa się z miejsca startowego, końcowego oraz dwukropka między nimi\n";
    std::cout << "Komenda może wyglądać np tak: k3x2:k1\n";
    std::cout << "To oznacza przenieść dwie karty (\"x2\") z trzeciej kolumny (\"k3\") do (\":\") pierwszej kolumny (\"k1\")\n";
    std::cout << "Gdy chcesz przeniesc karte na stos końcowy możesz użyć np. k1:sk\n";
    std::cout << "Czyli karta z kolumny pierwszej (\"k1\") na (\":\") odpowiedni stos końcowy (\"sk\")\n";
    std::cout << "Branie kart ze stosu rezerwowego też jest proste możesz do tego użyć np. sr:k3\n";
    std::cout << "Czyli karta ze stosu rezerwowego (\"sr\") na trzecia kolumne\n";
    std::cout << "Aby przeglądać stos rezerwowy możesz użyć sr:sr\n";
    std::cout << "\n Jeśli chcesz już grać nacisnij enter\n";

    std::cin.get();
}

/**
 * @brief Fills in the tableau waste and stock
 * 
 */
void Game::fillInCards(){
    //A loop that fills in the tableau
    for(int column = 0; column < 7; column++){
        tableau[column].resize(7); 
        for(int row = 0; row < column+1; row++){
            tableau[column][row] = Card(usedCards); 
            usedCards.push_back(tableau[column][row].text); 
            if(row != column){ 
                tableau[column][row].hide(); 
            }
        }
    }

    //Fill in the waste and stock
    while(usedCards.size() < 52){
        waste.push_back(Card(usedCards));
        usedCards.push_back(waste[waste.size()-1].text);
    }

}

/**
 * @brief Removes all cards that are empty from the tableau
 * 
 */
void Game::removeEmptyCards(){
    for(int i = 0; i < tableau.size(); i++){ 
        while(tableau[i][tableau[i].size()-1].text == "---"){ 
            tableau[i].pop_back();
        }
    }
}

void Game::executeCommand(){
    source = nullptr;
    destination = nullptr;
    if(command->isWasteScroll){
        if(wasteIndex < waste.size()-1){
            wasteIndex++; 
        }
        else{
            wasteIndex = 0; 
        }
        return;   
    }
    assignSource();
    getCardsToMove();
    if(!checkForHiddenCards()){
        return;
    }
    if(!assignDestination()){
        return;
    }
    if(!isCardOrderValid()){
        return;
    }
    moveCards();
    // for(const auto& karta : cardsToMove){
    //     std::cout << karta.text << "\n";
    // }
    // std::cout << "-----------------";
    // for(const auto& column : tableau){
    //     for(const auto& card : column){
    //         std::cout << card.text;
    //     }
    // }
}

void Game::assignSource(){
    switch(command->sourceType){
        case(1):
            source = &tableau[command->sourceIndex];
            break;
        case(2):
            source = &waste;
            break;
    }
}



void Game::getCardsToMove(){
    cardsToMove.clear();
    if(command->sourceType == 1){
        if(!source->empty()){
            if(command->amountOfCards == 1){
                cardsToMove.push_back(source->back());
                source->pop_back();

            } else {
                if(command->amountOfCards <= source->size()){
                    for(int i = 0; i < command->amountOfCards; i++){
                        cardsToMove.push_back(source->back());
                        source->pop_back();
                    }
                    if(!source->empty()){
                        source->back().show();
                    }
                }
            }
        }
    }

    if(command->sourceType == 2){
        if(source[wasteIndex].size() > 0){
            cardsToMove.push_back((*source)[wasteIndex]);
            waste.erase(waste.begin()+wasteIndex);
            if(wasteIndex >= waste.size()){
                if(wasteIndex > 0){
                    wasteIndex--;
                }
            }
        }
    }
}

void Game::revertMove(){
    while(!cardsToMove.empty()){ 
        source->push_back(cardsToMove.back());
        cardsToMove.pop_back(); 
    }
}

bool Game::checkForHiddenCards(){
    for(const auto& card : cardsToMove){
        if(card.isHidden){
            revertMove();
            std::cout << "Nie można przesuwać zakrytych kart!" << std::endl;
            return false;
        }
    }
    return true;
}

bool Game::assignDestination(){
    if(command->destinationType == 1){
        destination = &tableau[command->destinationIndex];
    }
    if(command->destinationType == 2){
        if(cardsToMove.size() != 1){
            revertMove();
            std::cout << "Nie można odkładać więcej niż jedną kartę na stos końcowy w jednym ruchu!";
            return false;
        }
        destination = &foundation[cardsToMove[0].suit];
    }
    return true;
}

bool Game::isCardOrderValid(){
    if((destination->empty() && command-> destinationType == 2) || (destination->empty() && cardsToMove.front().rank == 12)){
        return true;
    }
    if(cardsToMove.front().suit == 0 || cardsToMove.front().suit == 3){
        if(!(*destination).back().suit == 1 && !(*destination).back().suit == 2){
            revertMove();
            std::cout << "Karty czarne (♣,♠) mogą być przenoszone tylko na karty czerwone (♦,♥)";
            return false;
        }
    }
    else if(cardsToMove.front().suit == 1 || cardsToMove.front().suit == 2){
        if(!(*destination).back().suit == 0 && !(*destination).back().suit == 3){
            revertMove();
            std::cout << "Karty czerwone (♦,♥) mogą być przenoszone tylko na karty czarne (♣,♠)";
            return false;
        }
    }
    
    if(command->destinationType == 1){
        if(cardsToMove.back().rank >= (*destination).back().rank){
            revertMove();
            std::cout << "\nPrzesuwana karta/y musi być mniejsza od karty docelowej";
            return false;
        }
        if(cardsToMove.back().rank+1 < (*destination).back().rank){
            revertMove();
            std::cout << "\nPrzesuwana karta/y musi być mniejsza od karty docelowej";
            return false;
        }
    }
    if(command->destinationType == 2){
        if(cardsToMove.back().rank <= (*destination).back().rank){
            revertMove();
            std::cout << "\nKarty na stosie końcowym muszą być układane po kolei";
            return false;
        }
        if(cardsToMove.back().rank-1 != (*destination).back().rank){
            revertMove();
            std::cout << "\nKarty na stosie końcowym muszą być układane po kolei";
            return false;
        }
    }
    return true;
}

void Game::moveCards(){
    for(const auto& card : cardsToMove){
        (*destination).push_back(card);
    }
    if(!source->empty()){ 
        source->back().show();
    }
}