#include "card.h"

std::string ranks[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"}; 
std::string suits[4] = {"♣","♦","♥","♠"};

/**
 * @brief Creates a new card with a given rank and suit
 * 
 * @param rank Rank of the card
 * @param suit Suit of the card
 */
Card::Card(int rank, int suit){
    Card::rank = rank;
    Card::suit = suit;
    Card::text = ranks[rank] + suits[suit]; 
    if(Card::text.size() == 2){//Ensure the text is 3 chars long
        Card::text += " ";
    }
}

/**
 * @brief Creates a new random cards thats not in usedCards
 * 
 * @param usedCards Cards that have been already used
 */
Card::Card(std::vector<std::string> usedCards){
    while(true){
        Card::rank = rand() % 13; 
        Card::suit = rand() % 4; 
        Card::text = ranks[rank] + suits[suit]; 
        if(Card::text.size() == 4){//Ensure the text is 3 chars long
            Card::text += " ";
        }
        bool used = false; 
        for(int i = 0; i < usedCards.size(); i++){ 
            if(text == usedCards[i]){
                used = true;
                break; 
            }
        }
        if(!used){
            return; 
        }
    }
    
    
}


/**
 * @brief Creates a new empty card
 * 
 */
Card::Card(){
    Card::rank = NULL;
    Card::suit = NULL;
    Card::text = "---";
}

/**
 * @brief Hides the cars | Which mean change the text to "XX "
 * 
 */
void Card::hide(){
    Card::text = "XX";
    if(Card::text.size() == 2){
        Card::text += " ";
    }
    Card::isHidden = true;
}

/**
 * @brief Shows the card
 * 
 */
void Card::show(){
    Card::text = ranks[rank] + suits[suit]; 
    if(Card::text.size() == 2){
        Card::text += " ";
    }
    Card::isHidden = false;
}
