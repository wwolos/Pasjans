#include <Pasjans/card.h>

std::string ranks[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"}; 
std::string suits[4] = {"♣","♦","♥","♠"};
std::string safeSuits[4] = {"(Ż)","(D)","(C)","(W)"};

/**
 * @brief Creates a new card with a given rank and suit
 * 
 * @param rank Rank of the card
 * @param suit Suit of the card
 */
Card::Card(int rank, int suit){
    Card::rank = rank;
    Card::suit = suit;
    setTexts();
}

/**
 * @brief Creates a new random cards thats not in usedCards
 * 
 * @param usedCards Cards that have been already used
 */
Card::Card(std::vector<std::string> usedCards){
    if(usedCards.size() >= 52){
        throw std::runtime_error("Wszystkie karty wykorzystane");
    }
    Card::isHidden = false;
    while(true){
        Card::rank = rand() % 13; 
        Card::suit = rand() % 4; 
        setTexts();
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
    Card::rank = -1;
    Card::suit = -1;
    Card::text = "---";
}

/**
 * @brief Hides the cars | Which mean change the text to "XX "
 * 
 */
void Card::hide(){
    Card::text = "XX ";
    Card::safeText = "XXXX ";
    Card::isHidden = true;
}

/**
 * @brief Shows the card
 * 
 */
void Card::show(){
    setTexts();
    Card::isHidden = false;
}

void Card::setTexts(){
    Card::text = ranks[rank] + suits[suit]; 
    Card::safeText = ranks[rank] + safeSuits[suit]; 
    if(Card::rank != 9){
        Card::text += " ";
        Card::safeText += " ";
    }
}
