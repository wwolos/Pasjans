#ifndef CARD_H
#define CARD_H

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
    Card(int rank, int suit);
    Card(std::vector<std::string> usedCards);
    Card();
    void hide();
    void show();

   private:
    void setTexts();
};

#endif