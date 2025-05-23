#include <Pasjans/gameView.h>

/**
 * @brief Displays the game board(In the normal mode)
 *
 */
void GameView::normalDisplay(std::vector<std::vector<Card>> tableau, std::vector<std::vector<Card>> foundation,
                             std::vector<Card> waste, int wasteIndex) {
    // Check the length of the longest column in the tableau
    int longestColumn = checkLongestColumn(tableau);

    std::cout << std::endl << SEPARATOR30 << std::endl << "|";

    // Display the foundation
    for (int i = 0; i < 4; i++) {
        if (foundation[i].size() >= 1) {
            if (foundation[i].back().suit == 0 || foundation[i].back().suit == 3) {
                std::cout << rang::fg::black << foundation[i].back().text << rang::fg::reset << "|";
            }
            if (foundation[i].back().suit == 1 || foundation[i].back().suit == 2) {
                std::cout << rang::fg::red << foundation[i].back().text << rang::fg::reset << "|";
            }
        } else {
            switch (i) {
                case (0):
                    std::cout << rang::fg::black << " ♣ " << rang::fg::reset << "|";
                    break;
                case (1):
                    std::cout << rang::fg::red << " ♦ " << rang::fg::reset << "|";
                    break;
                case (2):
                    std::cout << rang::fg::red << " ♥ " << rang::fg::reset << "|";
                    break;
                case (3):
                    std::cout << rang::fg::black << " ♠ " << rang::fg::reset << "|";
                    break;
            }
        }
    }

    // Display the waste/stock
    if (waste.size() > 0) {
        if (waste[wasteIndex].suit == 0 || waste[wasteIndex].suit == 3) {
            std::cout << "   |XX |" << rang::fg::black << waste[wasteIndex].text << rang::fg::reset << "|";
        } else {
            std::cout << "   |XX |" << rang::fg::red << waste[wasteIndex].text << rang::fg::reset << "|";
        }
    } else {
        std::cout << "   |XX |XX |";
    }

    std::cout << std::endl << SEPARATOR30 << "";

    // Display the tableau
    for (int i = 0; i < longestColumn; i++) {
        std::cout << std::endl << "|";
        for (const auto &column : tableau) {
            if (i < column.size()) {
                if (!column[i].isHidden) {
                    if (column[i].suit == 0 || column[i].suit == 3) {
                        std::cout << rang::fg::black << column[i].text << rang::fg::reset << "|";
                    } else {
                        std::cout << rang::fg::red << column[i].text << rang::fg::reset << "|";
                    }
                } else {
                    std::cout << rang::fg::gray << column[i].text << rang::fg::reset << "|";
                }
            } else {
                std::cout << "   |";
            }
        }
    }

    std::cout << std::endl
              << SEPARATOR30 << std::endl
              << "| 1 | 2 | 3 | 4 | 5 | 6 | 7 |" << std::endl
              << SEPARATOR30 << std::endl;
}

/**
 * @brief Displays the game board(In the safe mode)
 *
 */
void GameView::safeDisplay(std::vector<std::vector<Card>> tableau, std::vector<std::vector<Card>> foundation,
                           std::vector<Card> waste, int wasteIndex) {
    // Check the length of the longest column in the tableau
    int longestColumn = checkLongestColumn(tableau);

    std::cout << std::endl << SEPARATOR44 << std::endl << "|";

    // Display the foundation
    for (int i = 0; i < 4; i++) {
        if (foundation[i].size() >= 1) {
            if (foundation[i].back().suit == 0 || foundation[i].back().suit == 3) {
                std::cout << rang::fg::black << foundation[i].back().safeText << rang::fg::reset << "|";
            }
            if (foundation[i].back().suit == 1 || foundation[i].back().suit == 2) {
                std::cout << rang::fg::red << foundation[i].back().safeText << rang::fg::reset << "|";
            }
        } else {
            switch (i) {
                case (0):
                    std::cout << rang::fg::black << " (ż) "
                              << "|" << rang::fg::reset;
                    break;
                case (1):
                    std::cout << rang::fg::red << " (D) "
                              << "|" << rang::fg::reset;
                    break;
                case (2):
                    std::cout << rang::fg::red << " (C) "
                              << "|" << rang::fg::reset;
                    break;
                case (3):
                    std::cout << rang::fg::black << " (W) "
                              << "|" << rang::fg::reset;
                    break;
            }
        }
    }

    // Display the waste/stock
    if (waste.size() > 0) {
        if (waste[wasteIndex].suit == 0 || waste[wasteIndex].suit == 3) {
            std::cout << "     |XXXX |" << rang::fg::black << waste[wasteIndex].safeText << rang::fg::reset << "|";
        } else {
            std::cout << "     |XXXX |" << rang::fg::red << waste[wasteIndex].safeText << rang::fg::reset << "|";
        }
    } else {
        std::cout << "     |XXXX |XXXX |";
    }

    std::cout << std::endl << SEPARATOR44 << "";

    // Display the tableau
    for (int i = 0; i < longestColumn; i++) {
        std::cout << std::endl << "|";
        for (const auto &column : tableau) {
            if (i < column.size()) {
                if (!column[i].isHidden) {
                    if (column[i].suit == 0 || column[i].suit == 3) {
                        std::cout << rang::fg::black << column[i].safeText << rang::fg::reset << "|";
                    } else {
                        std::cout << rang::fg::red << column[i].safeText << rang::fg::reset << "|";
                    }
                } else {
                    std::cout << rang::fg::gray << column[i].safeText << rang::fg::reset << "|";
                }
            } else {
                std::cout << "     |";
            }
        }
    }

    std::cout << std::endl
              << SEPARATOR44 << std::endl
              << "|  1  |  2  |  3  |  4  |  5  |  6  |  7  |" << std::endl
              << SEPARATOR44 << std::endl;
}

/**
 * @brief Checks the length of the longest column in the tableau
 *
 * @return int The length of the longest column
 */
int GameView::checkLongestColumn(std::vector<std::vector<Card>> tableau) {
    int longestColumn = 0;
    for (const auto &column : tableau) {
        if (column.size() > longestColumn) {
            longestColumn = column.size();
        }
    }
    return longestColumn;
}

/**
 * @brief Displays the win/gratulations screen
 *
 */
void GameView::winScreen() {
    std::cout << SEPARATOR44 << std::endl;
    std::cout << "Gratulacje, wygrałes!" << std::endl;
    std::cout << SEPARATOR44 << std::endl;
    std::cout << "Bardzo dziękuję za grę!" << std::endl;
    std::cout << SEPARATOR44 << std::endl;
    std::cout << "Aby wyjsc z gry nacisnij enter" << std::endl;
    std::cout << "Aby zagrac ponownie uruchom program jeszcze raz" << std::endl;
    std::cout << SEPARATOR44 << std::endl;
}

/**
 * @brief Displays the loss/give up screen
 *
 */
void GameView::giveUpScreen() {
    std::cout << SEPARATOR44 << std::endl;
    std::cout << "Niestety, nie udało się tym razem wygrać..." << std::endl;
    std::cout << SEPARATOR44 << std::endl;
    std::cout << "Bardzo dziękuję za grę!" << std::endl;
    std::cout << SEPARATOR44 << std::endl;
    std::cout << "Aby wyjsc z gry nacisnij enter" << std::endl;
    std::cout << "Aby zagrac ponownie uruchom program jeszcze raz" << std::endl;
    std::cout << SEPARATOR44 << std::endl;
}