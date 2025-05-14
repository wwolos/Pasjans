#include <catch2/catch_all.hpp>
#include <Pasjans/card.h>

TEST_CASE("Card constructor with rank and suit") {
    Card card(5, 2);
    REQUIRE(card.rank == 5);
    REQUIRE(card.suit == 2);
    REQUIRE(card.text == "6♥ ");
    REQUIRE(card.safeText == "6(C) ");
}

TEST_CASE("Card constructor with usedCards") {
    std::vector<std::string> usedCards;
    for(int i = 0; i < 51; i++){
        usedCards.push_back((*new Card(usedCards)).text);
        for(int j = 0; j < usedCards.size()-1; j++){
            REQUIRE(usedCards[j] != usedCards.back());
        }
    }
    Card card(usedCards);
    REQUIRE(card.rank >= 0);
    REQUIRE(card.rank <= 12);
    REQUIRE(card.suit >= 0);
    REQUIRE(card.suit <= 3);
    bool isCardInUsedCards = false;
    for(const auto& usedCard : usedCards){
        if(card.text == usedCard){
            isCardInUsedCards = true;
        }
    }
    REQUIRE(isCardInUsedCards == false);
    
    while(usedCards.size() < 52){
        usedCards.push_back((*new Card(usedCards)).text);
    }
    REQUIRE_THROWS(Card(usedCards));

    BENCHMARK("52 Random cards"){
        std::vector<std::string> usedCards;
        for(int i = 0; i < 52; i++){
            usedCards.push_back((*new Card(usedCards)).text);
        }
    };
}

TEST_CASE("Card show method") {
    Card card(0, 0);
    card.show();
    REQUIRE(card.text == "A♣ ");
    REQUIRE(card.isHidden == false);
}

TEST_CASE("Card show methodx10 on same card") {
    Card card(0, 0);
    for(int i = 0; i < 10; i++){
        card.show();
        REQUIRE(card.text == "A♣ ");
        REQUIRE(card.isHidden == false);
    }
}

TEST_CASE("Card hide method") {
    Card card(0, 0);
    card.hide();
    REQUIRE(card.text == "XX ");
    REQUIRE(card.isHidden == true);
}

TEST_CASE("Card hide methodx10 on same card") {
    Card card(0, 0);
    for(int i = 0; i < 10; i++){
        card.hide();
        REQUIRE(card.text == "XX ");
        REQUIRE(card.isHidden == true);
    }
}

