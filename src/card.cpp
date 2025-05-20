/**
 * @file card.cpp
 * @author Wiktor Wołos (wiktor_wolos@outlook.com)
 * @brief A class that represents a single card
 * @version 0.1
 * @date 2025-05-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <Pasjans/card.h>

const std::string Card::ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const std::string Card::suits[SUITS_COUNT] = {"♣", "♦", "♥", "♠"};
const std::string Card::safeSuits[SUITS_COUNT] = {"(Ż)", "(D)", "(C)", "(W)"};

/**
 * @brief Creates a new card with a given rank and suit
 *
 * @param rank Rank of the card
 * @param suit Suit of the card
 */
Card::Card(int rank, int suit) {
    Card::rank = rank;
    Card::suit = suit;
    Card::isHidden = false;
    setTexts();
}

/**
 * @brief Creates a new random cards thats not in usedCards
 *
 * @param usedCards Cards that have been already used
 */
Card::Card(std::vector<std::string> usedCards) {
    if (usedCards.size() >= 52) {
        throw std::runtime_error("Wszystkie karty wykorzystane");
    }
    Card::isHidden = false;
    while (true) {
        Card::rank = rand() % RANK_COUNT;
        Card::suit = rand() % SUITS_COUNT;
        setTexts();
        bool used = false;
        for (int i = 0; i < usedCards.size(); i++) {
            if (text == usedCards[i]) {
                used = true;
                break;
            }
        }
        if (!used) {
            return;
        }
    }
}

/**
 * @brief Creates a new empty card
 *
 */
Card::Card() {
    Card::rank = -1;
    Card::suit = -1;
    Card::text = "---";
}

/**
 * @brief Hides the cars | Which mean change the text to "XX "
 *
 */
void Card::hide() {
    Card::text = "XX ";
    Card::safeText = "XXXX ";
    Card::isHidden = true;
}

/**
 * @brief Shows the card
 *
 */
void Card::show() {
    setTexts();
    Card::isHidden = false;
}

/**
 * @brief Sets text, and safeText
 *
 */
void Card::setTexts() {
    Card::text = ranks[rank] + suits[suit];
    Card::safeText = ranks[rank] + safeSuits[suit];
    if (Card::rank != 9) {
        Card::text += " ";
        Card::safeText += " ";
    }
}
