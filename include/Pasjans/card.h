/**
 * @file card.h
 * @author Wiktor Wołos (wiktor_wolos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2025-05-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef CARD_H
#define CARD_H

#include <Pasjans/consts.h>

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief A class that represents a single card, it has a rank, suit and can be
 * hidden or shown
 *
 */
class Card {
   public:
    std::string text, safeText;  // Text used to display the card
    int rank, suit;              // This is stored as an index
    bool isHidden;
    static const std::string ranks[13];
    static const std::string suits[4];
    static const std::string safeSuits[4];
    Card(int rank, int suit);
    Card(std::vector<std::string> usedCards);
    Card();
    void hide();
    void show();

   private:
    void setTexts();
};

#endif