#include "game.h"


/**
 * @brief Display welcome message, setup the tableau, foundataion etc. 
 * 
 */
Game::Game(){
    srand(time(0)); //Make sure the RNG has a different seed so it doesn't generate the same numbers
    tableau.resize(7); 
    foundation.resize(4);

    controlsInfoMessage();

    fillInCards();
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
    Command command(input);
    if(command.isCorrect){
        std::cout << input;
    }
    else{
        std::cout << "Komenda: " << input << " jest niepoprawna, ponieważ:\n" << command.reason;
    }
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