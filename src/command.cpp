#include <Pasjans/command.h>

const char COLUMN = 'k';
const std::string FOUNDATION = "sk";
const std::string WASTE = "sr";
const std::string WASTE_SCROLL = "sr";
const std::string WASTE_SCROLL_ALTERNATIVE = "sr:sr";

/**
 * @brief Checks if the command is correct, and splits up the informations into
 * smaller pieces
 *
 * @param input The command to be processed
 */
Command::Command(std::string input) {
    isCorrect = true;
    if (input == WASTE_SCROLL || input == WASTE_SCROLL_ALTERNATIVE) {
        isWasteScroll = true;
        return;
    }
    if (input.find(":") == std::string::npos) {
        isCorrect = false;
        reason = "Komenda musi zawierać dwukropek.";
        return;
    }
    left = input.substr(0, input.find(":"));
    right = input.substr(input.find(":") + 1);
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
void Command::validateCommand() {
    validateLeftSide();
    validateRightSide();
}

/**
 * @brief Check if the left side of the command is valid
 *
 */
void Command::validateLeftSide() {
    isSourceAColumn = left[0] == COLUMN;
    bool isLeftLengthValid = (left.length() == 2 || left.length() == 4 || left.length() == 5);
    std::regex pattern("^k[1-7]x(1[0-3]|[1-9]|a)$");
    // Regex to check if the left side starts
    // with a k a number from 1 to 7 and ends
    // with an x and a number from 1 to 13 or a(all cards)
    // ex. "k8x7"-incorrect(first number too high)
    //"k2x5"-correct
    //"k4x09"-incorrect(second number cant have leading zeros)
    //"k3x50"-incorret(second number too high)
    bool isCardAmountValid = std::regex_match(left, pattern);
    bool isSourceColumnNumberValid = left[1] > '0' && left[1] <= '7';
    bool isSourceStock = left.substr(0, 2) == WASTE;

    if (!(isSourceAColumn || isSourceStock)) {
        isCorrect = false;
        reason = "W poprawnej komendzie lewa strona (przed dwukropkiem) musi zaczynać się od k lub sr";
        return;
    }
    if (isSourceAColumn) {
        if (!isSourceColumnNumberValid) {
            isCorrect = false;
            reason = "Po lewej stronie (przed dwukropkiem) po literze k zawsze musi być numer od 1-7";
            return;
        }
    }
    if (left.length() == 4) {
        if (!isCardAmountValid) {
            isCorrect = false;
            reason =
                "Jeśli część przed dwukropkiem zawiera więcej niż dwa znaki, musi kończyć się literą 'x' oraz liczbą z "
                "zakresu od 1 do 13";
            return;
        }
    }
    if (left.length() == 5) {
        if (!(isCardAmountValid && isdigit(left[4]))) {
            isCorrect = false;
            reason =
                "Jeśli część przed dwukropkiem zawiera więcej niż dwa znaki, musi kończyć się literą 'x' oraz liczbą z "
                "zakresu od 1 do 13";
            return;
        }
    }
    if (!isLeftLengthValid) {
        isCorrect = false;
        reason = "W poprawnej komendzie lewa strona (przed dwukropkiem) ma 2 lub 4 znaki, a prawa 2.";
        return;
    }
}

/**
 * @brief Check if the right side of the command is valid
 *
 */
void Command::validateRightSide() {
    isDestinationAColumn = right[0] == COLUMN;
    bool isRightLengthValid = (right.length() == 2);
    bool isDestinationFoundation = right.substr(0, 2) == FOUNDATION;
    bool isDestinationColumnNumberValid = right[1] > '0' && right[1] <= '7';

    if (!(isDestinationAColumn || isDestinationFoundation)) {
        isCorrect = false;
        reason = "W poprawnej komendzie prawa strona (po dwukropku) musi zaczynać się od k lub sk";
        return;
    }
    if (isDestinationAColumn) {
        if (!isDestinationColumnNumberValid) {
            isCorrect = false;
            reason = "Po prawej stronie (po dwukropku) po literze k zawsze musi byc liczba od 1-7";
            return;
        }
    }
    if (destinationType == destinationTypes::FOUNDATION && amountOfCards > 1 && !isFullColumMove) {
        isCorrect = false;
        reason = "Nie mozna przenosic wielu kart na stos koncowy w jednym ruchu";
        return;
    }
    if (!isRightLengthValid) {
        isCorrect = false;
        reason = "W poprawnej komendzie lewa strona (przed dwukropkiem) ma 2 lub 4 znaki, a prawa 2.";
        return;
    }
}

/**
 * @brief Assigns the source type
 *
 */
void Command::assignSourceType() {
    if (isSourceAColumn) {
        sourceType = sourceTypes::COLUMN;
    }
    if (left[0] == 's' && left[1] == 'r') {
        sourceType = sourceTypes::WASTE;
    }
}

/**
 * @brief Assings the type of the destination
 *
 */
void Command::assignDestinationType() {
    if (isDestinationAColumn) {
        destinationType = destinationTypes::COLUMN;
    } else {
        destinationType = destinationTypes::FOUNDATION;
    }
}

/**
 * @brief Assigns the indieces
 *
 */
void Command::assignTheIndices() {
    sourceIndex = left[1] - '0' - 1;
    destinationIndex = right[1] - '0' - 1;
}

/**
 * @brief Checks the amount of cards that need to be moved
 *
 */
void Command::checkTheAmount() {
    if (left.length() == 4) {
        amountOfCards = left[3] - '0';
    } else if (left.length() == 5) {
        amountOfCards = std::stoi(left.substr(3, 2));
    } else {
        amountOfCards = 1;
    }

    if (left.length() == 4 && left[3] == 'a') {
        isFullColumMove = true;
    }
}