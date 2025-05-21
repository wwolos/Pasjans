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
 * @brief Creates a new random card that is in cardsToUse
 *
 * @param cardsToUse Cards to pick one from
 */
Card::Card(std::vector<Card> &cardsToUse) {
    if (cardsToUse.empty()) {
        throw std::runtime_error("Wszystkie karty wykorzystane");
    }
    Card::isHidden = false;

    int index = rand() % cardsToUse.size();
    Card::rank = cardsToUse[index].rank;
    Card::suit = cardsToUse[index].suit;
    setTexts();
    std::swap(cardsToUse[index], cardsToUse.back());
    cardsToUse.pop_back();
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
 * @brief Hides the cards | Which means: change the text to "XX "
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
