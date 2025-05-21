#include <Pasjans/card.h>

#include <catch2/catch_all.hpp>

TEST_CASE("Card constructor with rank and suit") {
    Card card(5, 2);
    REQUIRE(card.rank == 5);
    REQUIRE(card.suit == 2);
    REQUIRE(card.text == "6♥ ");
    REQUIRE(card.safeText == "6(C) ");
}

TEST_CASE("Card constructor with usedCards") {
    // Prepare cardsToUse
    std::vector<Card> cardsToUse;
    for (int i = 0; i < SUITS_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            cardsToUse.push_back(Card(j, i));
        }
    }
    for (int i = 0; i < 10; i++) {
        cardsToUse.erase(cardsToUse.begin() + rand() % cardsToUse.size());
    }
    Card card(cardsToUse);
    REQUIRE(card.rank >= 0);
    REQUIRE(card.rank <= 12);
    REQUIRE(card.suit >= 0);
    REQUIRE(card.suit <= 3);
    bool isCardInCardsToUse = false;
    for (const auto& usedCard : cardsToUse) {
        if (card.text == usedCard.text) {
            isCardInCardsToUse = true;
        }
    }
    REQUIRE(isCardInCardsToUse == false);

    std::vector<Card> emptyCardsToUse;
    REQUIRE_THROWS(Card(emptyCardsToUse));

    BENCHMARK("52 Random cards") {
        // Prepare cardsToUse
        std::vector<Card> cardsToUse;
        for (int i = 0; i < SUITS_COUNT; i++) {
            for (int j = 0; j < RANK_COUNT; j++) {
                cardsToUse.push_back(Card(j, i));
            }
        }
        std::vector<std::string> usedCards;
        for (int i = 0; i < 52; i++) {
            new Card(cardsToUse);
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
    for (int i = 0; i < 10; i++) {
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
    for (int i = 0; i < 10; i++) {
        card.hide();
        REQUIRE(card.text == "XX ");
        REQUIRE(card.isHidden == true);
    }
}
