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
    std::cout << "   |XX |" << waste[wasteIndex].text << "|";

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

    std::cout << "\n=============================\n";
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
    std::vector<Card> cardsToMove;
    if(command->sourceType == 1){
        if(!tableau[command->sourceIndex].empty()){
            if(command->amountOfCards == 1){
                    cardsToMove.push_back(tableau[command->sourceIndex].back());
                    tableau[command->sourceIndex].pop_back();
                    tableau[command->sourceIndex].back().show();
            }
            else{
                if(command->amountOfCards <= tableau[command->sourceIndex].size()){
                    for(int i = 0; i < command->amountOfCards; i++){
                        cardsToMove.push_back(tableau[command->sourceIndex].back());
                        tableau[command->sourceIndex].pop_back();
                        tableau[command->sourceIndex].back().show();
                    }
                }
            }
        }
    }

    for(const auto& card : cardsToMove){
        std::cout << "1";
        if(card.isHidden){
        std::cout << "2";
            while(cardsToMove.size() > 0){
                std::cout << "3";
                tableau[command->sourceIndex].push_back(cardsToMove.back());
            }
            
            std::cout << "Nie można przesuwać zakrytych kart!";
            return;
        }
    }

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