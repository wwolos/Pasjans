/**
 * @file game.cpp
 * @author Wiktor Wołos (wiktor_wolos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2025-05-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <Pasjans/game.h>

/**
 * @brief Display welcome message, setup the tableau, foundataion etc.
 *
 * @param debugMode If true, the game will be in debug mode(Skips the settings)
 */
Game::Game(bool debugMode) {
    srand(time(0));  // Make sure the RNG has a different seed so it doesn't
                     // generate the same numbers
    displayMode = DisplayMode::NONE;
    tableau.resize(TABLEAU_SIZE);
    foundation.resize(SUITS_COUNT);
    fillInCards();
    removeEmptyCards();

    if (!debugMode) {
        while (displayMode == DisplayMode::NONE) {
            settingsPopup(true);
        }
        controlsInfoMessage();
    } else {
        displayMode = DisplayMode::SAFE;
    }
}

/**
 * @brief A function that chcecks if the input is a correct command(using Command), and if its correct executes it in
 * the selected mode
 *
 *  @example
 * - "k1:k2" moves a single card from colum one, to column two
 * - "k1x5:k2" moves 5 cards from column one, to column two
 * - "k1:sk" moves a single card from column one, to the foundation
 * - "sr:k1" moves a single card from waste to column one
 * - "sr" or "sr:sr" scrolls the waste
 *
 * @param input The input to check and execute
 *
 * @returns Additional text to be added to the log file
 *
 */
std::string Game::processInput(std::string input) {
    std::string validationResult = validateCommand(input);
    if (validationResult != "") {
        return validationResult;
    }
    CommandExecutionResult result = executeCommand();
    return generateErrorReport(result);
}

/**
 * @brief Checks if the player has won (If all the foundations are full)
 *
 * @return true if the player has won
 * @return false if the player has NOT won
 */
bool Game::checkForWin() {
    for (const auto &column : foundation) {
        if (column.empty() || column.back().rank != 12) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Checks if the command is possible to execute
 *
 * @param input The command to check
 * @return std::string if the command is possible to execute returns an empty string, otherwise returns the reason
 */
std::string Game::validateCommand(std::string input) {
    command = std::make_unique<Command>(input);
    if (command->isCorrect) {
        std::cout << input;
    } else {
        std::cout << "Komenda: " << input << " jest niepoprawna, ponieważ:" << std::endl << command->reason;
        return "The command: " + input + " is not correct becouse: \n" + command->reason;
    }
    return "";
}

/**
 * @brief Generates an error report, that gives all the information about the error and could help with debugging
 *
 * @param result The result of executing the command
 * @return std::string The generated report
 */
std::string Game::generateErrorReport(CommandExecutionResult result) {
    if (result != CommandExecutionResult::SUCCESS) {
        std::string output = "\n\n\nThe command was NOT executed corecctly, displaying additional info \n";
        output += "Tableau: \n";
        for (const auto &column : tableau) {
            output += "\n\t" + SEPARATOR30 + "\n\t";
            for (const auto &card : column) {
                output += card.text + " ";
            }
        }

        output += "\t" + SEPARATOR30 + "\n\n";

        output += "Waste/Stock: \n    ";
        for (const auto &card : waste) {
            output += card.text + " ";
        }

        output += "\n\tCurrent wasteIndex: ";
        output += std::to_string(wasteIndex);
        output += "\n\n";

        output += "Foundation: \n";
        for (int i = 0; i < 4; i++) {
            if (foundation[i].empty()) {
                output += "\t" + std::to_string(i) + ": empty \n";
            } else {
                output += "\t" + std::to_string(i) + ": ";
                for (const auto &card : foundation[i]) {
                    output += card.text + " ";
                }
                output += "\n";
            }
        }
        output += "\n\n";

        output += "Fault point: ";
        switch (result) {
            case CommandExecutionResult::UNABLE_TO_GET_CARDS_TO_MOVE:
                output += "Getting cards to move \n";
                break;
            case CommandExecutionResult::UNABLE_TO_CHECK_FOR_HIDDEN_CARDS:
                output += "Checking for hidden cards\n";
                break;
            case CommandExecutionResult::UNABLE_TO_ASSIGN_DESTINATION:
                output += "Assigning the destination\n";
                break;
            case CommandExecutionResult::UNABLE_TO_CHECK_CARD_ORDER:
                output += "Checking if the card order is valid\n";
                break;

            default:
                output += "Unable to identify the point of failure\n";
                break;
        }

        output += "\n\n";

        output += "Cards to move: ";
        if (!cardsToMove.empty()) {
            for (const auto &card : cardsToMove) {
                output += card.text + " ";
            }
            output += "\n\n";
        } else {
            output += "empty\n\n";
        }

        output += "Destination: \n";
        output += "\tIs null pointer: ";
        if (destination == nullptr) {
            output += "yes\n";
        } else {
            output += "no\n";
        }
        output += "\tContents: ";
        if (destination && !destination->empty()) {
            for (const auto &card : (*destination)) {
                output += card.text + " ";
            }
        }
        output += "\n\n";

        output += "Source: \n";
        output += "\tIs null pointer: ";
        if (source == nullptr) {
            output += "yes\n";
        } else {
            output += "no\n";
        }
        output += "\tContents: ";
        for (const auto &card : (*source)) {
            output += card.text + " ";
        }
        output += "\n\n";

        output += "\n\nIf issue persists contanct developer on discord: xtagz_69 \n\n";
        return output;
    }
    return "";
}

/**
 * @brief A function that displays informations about the game controls
 *
 */
void Game::controlsInfoMessage() {
    std::cout << "Sterowanie:" << std::endl;
    std::cout << "\tAby sterować w tej grze będziesz używać komend" << std::endl;
    std::cout << "\tKażda komenda składa się z miejsca startowego, końcowego oraz dwukropka między nimi" << std::endl;
    std::cout << "\tKomenda może wyglądać np tak: k3x2:k1" << std::endl;
    std::cout << "\tTo oznacza przenieść dwie karty (\"x2\") z trzeciej kolumny (\"k3\") do (\":\") pierwszej kolumny "
                 "(\"k1\")"
              << std::endl;
    std::cout << "\tGdy chcesz przeniesc karte na stos końcowy możesz użyć np. k1:sk" << std::endl;
    std::cout << "\tCzyli karta z kolumny pierwszej (\"k1\") na (\":\") odpowiedni stos końcowy (\"sk\")" << std::endl;
    std::cout << "\tBranie kart ze stosu rezerwowego też jest proste możesz do tego użyć np. sr:k3" << std::endl;
    std::cout << "\tCzyli karta ze stosu rezerwowego (\"sr\") na trzecia kolumne" << std::endl;
    std::cout << "\tAby przeniesc wszystkie karty które da się przeniesc z danej kolumny możesz użyc \"xa\"";
    std::cout << "\tCzyli np. \"k3xa:k1\" przeniesie wszystkie mozliwe karty z trzeciej kolumny do pierwszej kolumny"
              << std::endl;
    std::cout << "\tAby przeglądać stos rezerwowy możesz użyć sr:sr, lub sr" << std::endl;
    std::cout << "\tAby wyjsc z gry wprowadz komende exit" << std::endl;
    std::cout << "\tAby zobaczyc tą wiadomosć wprowadz komende help" << std::endl;
    std::cout << "\tAby zmienic ustawienia wprowadz komende settings" << std::endl;
    std::cout << "\n Jeśli chcesz już grać nacisnij enter" << std::endl;

    std::cin.get();
}

/**
 * @brief Fills in the tableau, waste and stock with random cards
 *
 */
void Game::fillInCards() {
    // Prepare cardsToUse
    for (int i = 0; i < SUITS_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            cardsToUse.push_back(Card(j, i));
        }
    }

    // A loop that fills in the tableau
    for (int column = 0; column < TABLEAU_SIZE; column++) {
        tableau[column].resize(TABLEAU_SIZE);
        for (int row = 0; row < column + 1; row++) {
            tableau[column][row] = Card(cardsToUse);
            if (row != column) {
                tableau[column][row].hide();
            }
        }
    }

    // Fill in the waste and stock
    while (!cardsToUse.empty()) {
        waste.push_back(Card(cardsToUse));
    }
}

/**
 * @brief Removes all cards that are empty from the tableau
 *
 */
void Game::removeEmptyCards() {
    for (int i = 0; i < tableau.size(); i++) {
        while (tableau[i][tableau[i].size() - 1].text == "---") {
            tableau[i].pop_back();
        }
    }
}

/**
 * @brief Attempts to execute a command
 *
 * @return Game::CommandExecutionResult The result of trying to execute the command
 */
Game::CommandExecutionResult Game::executeCommand() {
    source = nullptr;
    destination = nullptr;
    if (command->isWasteScroll) {
        if (wasteIndex < waste.size() - 1) {
            wasteIndex++;
        } else {
            wasteIndex = 0;
        }
        return CommandExecutionResult::SUCCESS;
    }
    assignSource();
    if (!getCardsToMove()) {
        return CommandExecutionResult::UNABLE_TO_GET_CARDS_TO_MOVE;
    }
    if (!checkForHiddenCards()) {
        return CommandExecutionResult::UNABLE_TO_CHECK_FOR_HIDDEN_CARDS;
    }
    if (!assignDestination()) {
        return CommandExecutionResult::UNABLE_TO_ASSIGN_DESTINATION;
    }
    if (!isCardOrderValid()) {
        return CommandExecutionResult::UNABLE_TO_CHECK_CARD_ORDER;
    }
    moveCards();
    return CommandExecutionResult::SUCCESS;
}

/**
 * @brief Assign the pointer to the source(place to move cards from)
 *
 */
void Game::assignSource() {
    switch (command->sourceType) {
        case (Command::sourceTypes::COLUMN):
            source = &tableau[command->sourceIndex];
            break;
        case (Command::sourceTypes::WASTE):
            source = &waste;
            break;
    }
}

/**
 * @brief  Fills in cardsToMove
 *
 * @return true If cardsToMove was filled
 * @return false If cardsToMove was NOT filled, becouse its not possible
 */
bool Game::getCardsToMove() {
    cardsToMove.clear();
    if (command->sourceType == Command::sourceTypes::COLUMN && !command->isFullColumMove) {
        if (!source->empty()) {
            if (command->amountOfCards == 1) {
                cardsToMove.push_back(source->back());
                source->pop_back();

            } else {
                if (command->amountOfCards <= source->size()) {
                    for (int i = 0; i < command->amountOfCards; i++) {
                        cardsToMove.push_back(source->back());
                        source->pop_back();
                    }
                }
            }
        }
    }

    if (command->sourceType == Command::sourceTypes::COLUMN && command->isFullColumMove) {
        while (!source->empty()) {
            if (source->back().isHidden) {
                break;
            }

            if ((*source).size() > 1 && !(*source)[source->size() - 2].isHidden) {
                if (source->back().rank >= (*source)[source->size() - 2].rank) {
                    break;
                }
                if (source->back().rank + 1 < (*source)[source->size() - 2].rank) {
                    break;
                }
                if (source->back().suit == 0 || source->back().suit == 3) {
                    if ((*source)[source->size() - 2].suit == 0 || (*source)[source->size() - 2].suit == 3) {
                        break;
                    }
                }
                if (source->back().suit == 1 || source->back().suit == 2) {
                    if ((*source)[source->size() - 2].suit == 1 || (*source)[source->size() - 2].suit == 2) {
                        break;
                    }
                }
            }
            cardsToMove.push_back(source->back());
            source->pop_back();
        }
    }

    if (command->sourceType != Command::sourceTypes::COLUMN && command->isFullColumMove) {
        std::cout << "Mozna przesuwac wszystkie karty tylko z kolumny" << std::endl;
        return false;
    }

    if (wasteIndex > waste.size() && waste.size() > 0) {
        wasteIndex = 0;
    }

    if (command->sourceType == Command::sourceTypes::WASTE) {
        if ((*source).size() == 0) {
            return false;
        }
        if ((*source).size() > wasteIndex) {
            cardsToMove.push_back((*source)[wasteIndex]);
            waste.erase(waste.begin() + wasteIndex);
            if (wasteIndex >= waste.size()) {
                if (wasteIndex > 0) {
                    wasteIndex = 0;
                }
            } else {
                if (wasteIndex > 0) {
                    wasteIndex--;
                }
            }
        }
    }
    return true;
}

/**
 * @brief Puts the cards from cardsToMove back to the source
 *
 */
void Game::revertMove() {
    if (command->sourceType == Command::sourceTypes::COLUMN) {
        while (!cardsToMove.empty()) {
            source->push_back(cardsToMove.back());
            cardsToMove.pop_back();
        }
    } else {
        if (!cardsToMove.empty()) {
            source->insert(source->begin() + wasteIndex, cardsToMove[0]);
        }
    }
}

/**
 * @brief Checks if there are any hidden cards in cardsToMove
 *
 * @return true If there AREN'T any hidden cards
 * @return false If there is at least one hidden card
 */
bool Game::checkForHiddenCards() {
    for (const auto &card : cardsToMove) {
        if (card.isHidden) {
            revertMove();
            std::cout << "Nie można przesuwać zakrytych kart!" << std::endl;
            return false;
        }
    }
    return true;
}

/**
 * @brief Assigns the destination pointer(place to move the cards to)
 *
 * @return true If the operation was successful
 * @return false If the operation was NOT successful
 */
bool Game::assignDestination() {
    if (command->destinationType == Command::destinationTypes::COLUMN) {
        destination = &tableau[command->destinationIndex];
    }
    if (command->destinationType == Command::destinationTypes::FOUNDATION) {
        if (cardsToMove.empty()) {
            revertMove();
            std::cout << "Nie mozna odkladac zero kart na stos koncowy" << std::endl;
            return false;
        }
        if (cardsToMove.size() != 1) {
            revertMove();
            std::cout << "Nie można odkładać więcej niż jedną kartę na stos końcowy w jednym ruchu!";
            return false;
        }
        destination = &foundation[cardsToMove[0].suit];
    }
    return true;
}

/**
 * @brief Checks if the order of the cards is valid
 *
 * @return true If the order of the cards is valid
 * @return false  If the order of the cards is NOT valid
 */
bool Game::isCardOrderValid() {
    if ((destination->empty() && command->destinationType == Command::destinationTypes::FOUNDATION &&
         cardsToMove.back().rank != 0)) {
        revertMove();
        std::cout << "Na pusty stos koncowy mozna przeniesc tylko Asa";
        return false;
    }
    if (command->destinationType == Command::destinationTypes::COLUMN && destination->empty() &&
        cardsToMove.back().rank != 12) {
        revertMove();
        std::cout << "Na puste miejsce mozna prznosic tylko Krola";
        return false;
    }

    if (!destination->empty() && command->destinationType != Command::destinationTypes::FOUNDATION) {
        if (destination->back().suit == 0 || destination->back().suit == 3) {
            if (cardsToMove.back().suit == 0 || cardsToMove.back().suit == 3) {
                revertMove();
                std::cout << std::endl << "Czerwone karty mozna przekladac tylko na czarne a czarne tylko na czerwone";
                return false;
            }
        }
        if (destination->back().suit == 1 || destination->back().suit == 2) {
            if (cardsToMove.back().suit == 1 || cardsToMove.back().suit == 2) {
                revertMove();
                std::cout << std::endl << "Czerwone karty mozna przekladac tylko na czarne a czarne tylko na czerwone";
                return false;
            }
        }
    }

    if (command->destinationType == Command::destinationTypes::COLUMN) {
        if (!(*destination).empty() && cardsToMove.back().rank >= (*destination).back().rank) {
            revertMove();
            std::cout << std::endl << "Przesuwana karta/y musi być mniejsza od karty docelowej";
            return false;
        }
        if (!(*destination).empty() && cardsToMove.back().rank + 1 < (*destination).back().rank) {
            revertMove();
            std::cout << std::endl << "Przesuwana karta/y musi być mniejsza od karty docelowej";
            return false;
        }
    }
    if (command->destinationType == Command::destinationTypes::FOUNDATION) {
        if (!destination->empty()) {
            if (cardsToMove.back().rank <= (*destination).back().rank) {
                revertMove();
                std::cout << std::endl << "Karty na stosie końcowym muszą być układane po kolei";
                return false;
            }
            if (cardsToMove.back().rank - 1 != (*destination).back().rank) {
                revertMove();
                std::cout << std::endl << "Karty na stosie końcowym muszą być układane po kolei";
                return false;
            }
        } else {
            if (cardsToMove.back().rank != 0) {
                revertMove();
                std::cout << std::endl << "Na pusty stos koncowy mozna przenosic tylko Asa";
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Moves the cards from cardsToMove to the destination
 *
 */
void Game::moveCards() {
    while (!cardsToMove.empty()) {
        (*destination).push_back(cardsToMove.back());
        cardsToMove.pop_back();
    }

    if (!source->empty()) {
        source->back().show();
    }
}

/**
 * @brief Shows the settings menu
 *
 */
void Game::settingsPopup(bool isFirstTime) {
    std::cout << "\033[2J\033[1;1H";
    if (isFirstTime) {
        std::cout << "Aby gra mogła poprawnie działać proszę o wybranie trybu wyswietlania." << std::endl;
    }
    std::cout << "Ustawienia:\t" << std::endl;
    std::cout << "\t1. TRYB WYSWIETLANIA" << std::endl;

    std::string setting;
    std::getline(std::cin, setting);
    if (setting == "1") {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "TRYB WYSWIETLANIA:\t" << std::endl;
        std::cout << "\t1. NORMALNY (Może nie działać na Windowsie)" << std::endl;
        std::cout << "\t2. BEZPIECZNY" << std::endl;

        std::string option;
        std::getline(std::cin, option);
        if (option == "1") {
            displayMode = DisplayMode::NORMAL;
        } else if (option == "2") {
            displayMode = DisplayMode::SAFE;
        } else {
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Niepoprawna opcja." << std::endl << "Nacisnij enter aby kontynuować...";
            std::cin.get();
            return;
        }
        std::cout << "\033[2J\033[1;1H";
    } else {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Niepoprawna opcja." << std::endl << "Nacisnij enter aby kontynuować...";
        std::cin.get();
        std::cout << "\033[2J\033[1;1H";
        return;
    }
}
